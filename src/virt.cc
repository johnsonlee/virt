/**
 * libvirt for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node
#include <node.h>
#include <node_object_wrap.h>

// libvirt
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#include "native-class.h"
#include "throw.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TRACE() printf("%s#%d\n", __FUNCTION__, __LINE__)

#define CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, argc) \
    do {                                                         \
        if ((args).Length() < (argc)) {                          \
            throwError((isolate), "Too few arguments");          \
            return;                                              \
        }                                                        \
                                                                 \
        if (!(args)[0]->IsObject()) {                            \
            throwTypeError((isolate), "Invalid arguments");      \
            return;                                              \
        }                                                        \
    } while (0);

#define CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native) \
    do {                                                         \
        if (NULL == (native)) {                                  \
            throwError((isolate), "Invalid arguments");          \
            return;                                              \
        }                                                        \
                                                                 \
        if ((native)->IsEmpty()) {                               \
            return;                                              \
        }                                                        \
    } while (0);

#define CHK_ARGUMENT_TYPE(isolate, arg, type)                    \
    do {                                                         \
        if (!arg->Is ## type()) {                                \
            throwTypeError(isolate, "Invalid arguments");        \
            return;                                              \
        }                                                        \
    } while (0);

static void __virConnectBaselineCPU(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);

    // check arg1
    CHK_ARGUMENT_TYPE(isolate, args[1], Array);
    v8::Local<v8::Array> cpus = v8::Local<v8::Array>::Cast(args[1]);
    for (unsigned int i = 0, n = (*cpus)->Length(); i < n; i++) {
        v8::Local<v8::Value> item = cpus->Get(i);
        CHK_ARGUMENT_TYPE(isolate, item, String);
    }

    // check arg2
    CHK_ARGUMENT_TYPE(isolate, args[2], Uint32);

    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    unsigned int ncpus = (*cpus)->Length();
    unsigned int flags = args[2]->Uint32Value();
    char **xmlCPU = new char*[ncpus];

    for (unsigned int i = 0; i < ncpus; i++) {
        v8::String::Utf8Value xml(cpus->Get(i)->ToString());
        xmlCPU[i] = strdup(*xml);
    }

    char *cpu = virConnectBaselineCPU(conn, const_cast<const char**>(xmlCPU), ncpus, flags);

    for (unsigned int i = 0; i < ncpus; i++) {
        free(xmlCPU[i]);
    }
    delete xmlCPU;

    if (NULL == cpu) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, cpu));
    free(cpu);
}

static void __virConnectOpen(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    virConnectPtr conn = NULL;

    if (0 == args.Length() || args[0]->IsUndefined() || args[0]->IsNull()) {
        conn = virConnectOpen(NULL);
    } else if (!args[0]->IsString()) {
        throwTypeError(isolate, "Invalid argument");
        return;
    } else {
        v8::String::Utf8Value name(args[0]->ToString());
        conn = virConnectOpen(*name);
    }

    if (NULL == conn) {
        throwVirtError(isolate);
    } else {
        NativeClass::NewInstance(conn, args);
    }
}

static void __virConnectClose(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);

    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);

    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int result = virConnectClose(conn);
    if (-1 != result) {
        native->Clear();
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, result));
}

static void __virGetVersion(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    unsigned long libVer = 0;

    if (-1 == virGetVersion(&libVer, NULL, NULL)) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, libVer));
}

void initialize(v8::Handle<v8::Object> exports) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();

    if (0 != virInitialize()) {
        throwVirtError(isolate);
        return;
    }

    NativeClass::Export(exports, "Connection");

    NODE_SET_METHOD(exports, "virConnectBaselineCPU", __virConnectBaselineCPU);
    NODE_SET_METHOD(exports, "virConnectClose",       __virConnectClose);
    NODE_SET_METHOD(exports, "virConnectOpen",        __virConnectOpen);
    NODE_SET_METHOD(exports, "virGetVersion",         __virGetVersion);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, initialize)
