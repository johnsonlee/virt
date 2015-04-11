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

static void __virConnectCompareCPU(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);
    CHK_ARGUMENT_TYPE(isolate, args[1], String);
    CHK_ARGUMENT_TYPE(isolate, args[2], Uint32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    v8::String::Utf8Value xml(args[1]->ToString());
    unsigned int flags = args[2]->Uint32Value();
    int result = virConnectCompareCPU(conn, *xml, flags);
    if (VIR_CPU_COMPARE_ERROR == result) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, result));
}

static void __virConnectGetCapabilities(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    char *xml = virConnectGetCapabilities(conn);
    if (NULL == xml) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, xml));
    free(xml);
}

static void __virConnectGetHostname(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    char *hostname = virConnectGetHostname(conn);
    if (NULL == hostname) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, hostname));
    free(hostname);
}

static void __virConnectGetLibVersion(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned long ver = 0;
    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    if (-1 == virConnectGetLibVersion(conn, &ver)) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, ver));
}

static void __virConnectGetMaxVcpus(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 2);
    CHK_ARGUMENT_TYPE(isolate, args[1], String);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    v8::String::Utf8Value type(args[1]->ToString());
    int max = virConnectGetMaxVcpus(conn, *type);
    if (-1 == max) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, max));
}

static void __virConnectGetSysinfo(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    char *xml = virConnectGetSysinfo(conn, 0);
    if (NULL == xml) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, xml));
    free(xml);
}

static void __virConnectGetType(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    const char *type = virConnectGetType(conn);
    if (NULL == type) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, type));
}

static void __virConnectGetURI(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    const char *uri = virConnectGetURI(conn);
    if (NULL == uri) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, uri));
}

static void __virConnectGetVersion(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned long ver;
    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    if (-1 == virConnectGetVersion(conn, &ver)) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, ver));
}

static void __virConnectIsAlive(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int alive = virConnectIsAlive(conn);
    if (-1 == alive) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Boolean::New(isolate, alive != 0));
}

static void __virConnectIsEncrypted(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int encrypted = virConnectIsEncrypted(conn);
    if (-1 == encrypted) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Boolean::New(isolate, encrypted != 0));
}

static void __virConnectIsSecure(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int secure = virConnectIsSecure(conn);
    if (-1 == secure) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Boolean::New(isolate, secure != 0));
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

static void __virConnectOpenReadOnly(const v8::FunctionCallbackInfo<v8::Value>& args) {
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
        conn = virConnectOpenReadOnly(*name);
    }

    if (NULL == conn) {
        throwVirtError(isolate);
    } else {
        NativeClass::NewInstance(conn, args);
    }
}

static void __virConnectRef(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int result = virConnectRef(conn);
    if (-1 == result) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Boolean::New(isolate, 0 == result));
}

static void __virConnectSetKeepAlive(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);
    CHK_ARGUMENT_TYPE(isolate, args[1], Int32);
    CHK_ARGUMENT_TYPE(isolate, args[2], Uint32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int interval = args[1]->Int32Value();
    unsigned int count = args[2]->Uint32Value();
    int result = virConnectSetKeepAlive(conn, interval, count);
    if (-1 == result) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Boolean::New(isolate, 0 == result));
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

static void __virNodeGetCPUMap(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    unsigned char *cpumap = NULL;
    int ncpu = virNodeGetCPUMap(conn, &cpumap, NULL, 0);
    if (-1 == ncpu) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::ArrayBuffer::New(isolate, cpumap, ncpu));

    if (NULL != cpumap) {
        free(cpumap);
    }
}

static void __virNodeGetCPUStats(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 2);
    CHK_ARGUMENT_TYPE(isolate, args[1], Int32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int nparams = 0;
    int cpuNum = args[1]->Int32Value();

    if (0 != virNodeGetCPUStats(conn, cpuNum, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virNodeCPUStatsPtr params = static_cast<virNodeCPUStatsPtr>(calloc(nparams, sizeof(virNodeCPUStats)));

    if (0 != virNodeGetCPUStats(conn, cpuNum, params, &nparams, 0)) {
        throwVirtError(isolate);
    } else {
        v8::Local<v8::Object> result = v8::Object::New(isolate);
        for (int i = 0; i < nparams; i++) {
            virNodeCPUStatsPtr param = params + i;
            result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value));
        }
        args.GetReturnValue().Set(result);
    }

    free(params);
}

static void __virNodeGetCellsFreeMemory(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);
    CHK_ARGUMENT_TYPE(isolate, args[1], Int32);
    CHK_ARGUMENT_TYPE(isolate, args[2], Int32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int start = args[1]->Int32Value();
    int max = args[2]->Int32Value();
    unsigned long long *mems = static_cast<unsigned long long*>(calloc(max - start + 1, sizeof(unsigned long long)));
    int n = virNodeGetCellsFreeMemory(conn, mems, start, max);

    if (-1 == n) {
        throwVirtError(isolate);
    } else {
        v8::Local<v8::Array> result = v8::Array::New(isolate, n);
        for (int i = 0; i < n; i++) {
            result->Set(i, v8::Number::New(isolate, mems[i]));
        }
        args.GetReturnValue().Set(result);
    }

    free(mems);
}

static void __virNodeGetFreeMemory(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    unsigned long long mem = virNodeGetFreeMemory(conn);
    if (mem <= 0) {
        throwVirtError(isolate);
        return;
    }

    args.GetReturnValue().Set(v8::Number::New(isolate, mem));
}

static void __virNodeGetInfo(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    virNodeInfo info;
    memset(&info, 0, sizeof(info));
    if (0 != virNodeGetInfo(conn, &info)) {
        throwVirtError(isolate);
        return;
    }

    v8::Local<v8::Object> result = v8::Object::New(isolate);
    result->Set(v8::String::NewFromUtf8(isolate, "model"), v8::String::NewFromUtf8(isolate, info.model));
    result->Set(v8::String::NewFromUtf8(isolate, "memory"), v8::Number::New(isolate, info.memory));
    result->Set(v8::String::NewFromUtf8(isolate, "cpus"), v8::Number::New(isolate, info.cpus));
    result->Set(v8::String::NewFromUtf8(isolate, "mhz"), v8::Number::New(isolate, info.mhz));
    result->Set(v8::String::NewFromUtf8(isolate, "nodes"), v8::Number::New(isolate, info.nodes));
    result->Set(v8::String::NewFromUtf8(isolate, "sockets"), v8::Number::New(isolate, info.sockets));
    result->Set(v8::String::NewFromUtf8(isolate, "cores"), v8::Number::New(isolate, info.cores));
    result->Set(v8::String::NewFromUtf8(isolate, "threads"), v8::Number::New(isolate, info.threads));
    args.GetReturnValue().Set(result);
}

static void __virNodeGetMemoryParameters(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int nparams = 0;
    if (0 != virNodeGetMemoryParameters(conn, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virTypedParameterPtr params = static_cast<virTypedParameterPtr>(calloc(nparams, sizeof(virTypedParameter)));

    if (0 != virNodeGetMemoryParameters(conn, params, &nparams, 0)) {
        throwVirtError(isolate);
    } else {
        v8::Local<v8::Object> result = v8::Object::New(isolate);

        for (int i = 0; i < nparams; i++) {
            virTypedParameterPtr param = params + i;

            switch (param->type) {
            case VIR_TYPED_PARAM_INT:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value.i));
                break;
            case VIR_TYPED_PARAM_UINT:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value.ui));
                break;
            case VIR_TYPED_PARAM_LLONG:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value.l));
                break;
            case VIR_TYPED_PARAM_ULLONG:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value.ul));
                break;
            case VIR_TYPED_PARAM_DOUBLE:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value.d));
                break;
            case VIR_TYPED_PARAM_BOOLEAN:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Boolean::New(isolate, 0 != param->value.b));
                break;
            case VIR_TYPED_PARAM_STRING:
                result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::String::NewFromUtf8(isolate, param->value.s));
                break;
            }
        }

        args.GetReturnValue().Set(result);
    }

    free(params);
}

static void __virNodeGetMemoryStats(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 2);
    CHK_ARGUMENT_TYPE(isolate, args[1], Int32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    int cellNum = args[1]->Int32Value();    
    int nparams = 0;

    if (0 != virNodeGetMemoryStats(conn, cellNum, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virNodeMemoryStatsPtr params = static_cast<virNodeMemoryStatsPtr>(calloc(nparams, sizeof(virNodeMemoryStats)));

    if (0 != virNodeGetMemoryStats(conn, cellNum, params, &nparams, 0)) {
        throwVirtError(isolate);
    } else {
        v8::Local<v8::Object> result = v8::Object::New(isolate);

        for (int i = 0; i < nparams; i++)  {
            virNodeMemoryStatsPtr param = params + i;
            result->Set(v8::String::NewFromUtf8(isolate, param->field), v8::Number::New(isolate, param->value));
        }

        args.GetReturnValue().Set(result);
    }

    free(params);
}

static void __virNodeGetSecurityModel(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    NativeClass *native = node::ObjectWrap::Unwrap<NativeClass>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virConnectPtr conn = static_cast<virConnectPtr>(**native);
    virSecurityModel secmodel;
    memset(&secmodel, 0, sizeof(virSecurityModel));
    if (0 != virNodeGetSecurityModel(conn, &secmodel)) {
        throwVirtError(isolate);
        return;
    }

    v8::Local<v8::Object> result = v8::Object::New(isolate);
    result->Set(v8::String::NewFromUtf8(isolate, "model"), v8::String::NewFromUtf8(isolate, secmodel.model));
    result->Set(v8::String::NewFromUtf8(isolate, "doi"), v8::String::NewFromUtf8(isolate, secmodel.doi));
    args.GetReturnValue().Set(result);
}

void initialize(v8::Handle<v8::Object> exports) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();

    if (0 != virInitialize()) {
        throwVirtError(isolate);
        return;
    }

    NativeClass::Export(exports, "Connection");

    NODE_SET_METHOD(exports, "virConnectBaselineCPU",      __virConnectBaselineCPU);
    NODE_SET_METHOD(exports, "virConnectClose",            __virConnectClose);
    NODE_SET_METHOD(exports, "virConnectCompareCPU",       __virConnectCompareCPU);
    NODE_SET_METHOD(exports, "virConnectGetCapabilities",  __virConnectGetCapabilities);
    NODE_SET_METHOD(exports, "virConnectGetHostname",      __virConnectGetHostname);
    NODE_SET_METHOD(exports, "virConnectGetLibVersion",    __virConnectGetLibVersion);
    NODE_SET_METHOD(exports, "virConnectGetMaxVcpus",      __virConnectGetMaxVcpus);
    NODE_SET_METHOD(exports, "virConnectGetSysinfo",       __virConnectGetSysinfo);
    NODE_SET_METHOD(exports, "virConnectGetType",          __virConnectGetType);
    NODE_SET_METHOD(exports, "virConnectGetURI",           __virConnectGetURI);
    NODE_SET_METHOD(exports, "virConnectGetVersion",       __virConnectGetVersion);
    NODE_SET_METHOD(exports, "virConnectIsAlive",          __virConnectIsAlive);
    NODE_SET_METHOD(exports, "virConnectIsEncrypted",      __virConnectIsEncrypted);
    NODE_SET_METHOD(exports, "virConnectIsSecure",         __virConnectIsSecure);
    NODE_SET_METHOD(exports, "virConnectOpen",             __virConnectOpen);
    NODE_SET_METHOD(exports, "virConnectOpenReadOnly",     __virConnectOpenReadOnly);
    NODE_SET_METHOD(exports, "virConnectRef",              __virConnectRef);
    NODE_SET_METHOD(exports, "virConnectSetKeepAlive",     __virConnectSetKeepAlive);
    NODE_SET_METHOD(exports, "virGetVersion",              __virGetVersion);
    NODE_SET_METHOD(exports, "virNodeGetCPUMap",           __virNodeGetCPUMap);
    NODE_SET_METHOD(exports, "virNodeGetCPUStats",         __virNodeGetCPUStats);
    NODE_SET_METHOD(exports, "virNodeGetCellsFreeMemory",  __virNodeGetCellsFreeMemory);
    NODE_SET_METHOD(exports, "virNodeGetFreeMemory",       __virNodeGetFreeMemory);
    NODE_SET_METHOD(exports, "virNodeGetInfo",             __virNodeGetInfo);
    NODE_SET_METHOD(exports, "virNodeGetMemoryParameters", __virNodeGetMemoryParameters);
    NODE_SET_METHOD(exports, "virNodeGetMemoryStats",      __virNodeGetMemoryStats);
    NODE_SET_METHOD(exports, "virNodeGetSecurityModel",    __virNodeGetSecurityModel);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, initialize)
