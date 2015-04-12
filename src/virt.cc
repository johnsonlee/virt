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

#include "connection.h"
#include "domain.h"
#include "interface.h"

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
        if ((native)->IsNull()) {                               \
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned int ncpus = (*cpus)->Length();
    unsigned int flags = args[2]->Uint32Value();
    char **xmlCPU = new char*[ncpus];

    for (unsigned int i = 0; i < ncpus; i++) {
        v8::String::Utf8Value xml(cpus->Get(i)->ToString());
        xmlCPU[i] = strdup(*xml);
    }

    char *cpu = virConnectBaselineCPU(**native, const_cast<const char**>(xmlCPU), ncpus, flags);

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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int result = virConnectClose(**native);
    if (-1 != result) {
        native->SetNull();
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    v8::String::Utf8Value xml(args[1]->ToString());
    unsigned int flags = args[2]->Uint32Value();
    int result = virConnectCompareCPU(**native, *xml, flags);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    char *xml = virConnectGetCapabilities(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    char *hostname = virConnectGetHostname(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned long ver = 0;
    if (-1 == virConnectGetLibVersion(**native, &ver)) {
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    v8::String::Utf8Value type(args[1]->ToString());
    int max = virConnectGetMaxVcpus(**native, *type);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    char *xml = virConnectGetSysinfo(**native, 0);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    const char *type = virConnectGetType(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    const char *uri = virConnectGetURI(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned long ver;
    if (-1 == virConnectGetVersion(**native, &ver)) {
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int alive = virConnectIsAlive(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int encrypted = virConnectIsEncrypted(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int secure = virConnectIsSecure(**native);
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
        Connection::NewInstance<Connection>(conn, args);
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
        Connection::NewInstance<Connection>(conn, args);
    }
}

static void __virConnectRef(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int result = virConnectRef(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int interval = args[1]->Int32Value();
    unsigned int count = args[2]->Uint32Value();
    int result = virConnectSetKeepAlive(**native, interval, count);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned char *cpumap = NULL;
    int ncpu = virNodeGetCPUMap(**native, &cpumap, NULL, 0);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int nparams = 0;
    int cpuNum = args[1]->Int32Value();

    if (0 != virNodeGetCPUStats(**native, cpuNum, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virNodeCPUStatsPtr params = static_cast<virNodeCPUStatsPtr>(calloc(nparams, sizeof(virNodeCPUStats)));

    if (0 != virNodeGetCPUStats(**native, cpuNum, params, &nparams, 0)) {
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int start = args[1]->Int32Value();
    int max = args[2]->Int32Value();
    unsigned long long *mems = static_cast<unsigned long long*>(calloc(max - start + 1, sizeof(unsigned long long)));
    int n = virNodeGetCellsFreeMemory(**native, mems, start, max);

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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned long long mem = virNodeGetFreeMemory(**native);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virNodeInfo info;
    memset(&info, 0, sizeof(info));
    if (0 != virNodeGetInfo(**native, &info)) {
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int nparams = 0;
    if (0 != virNodeGetMemoryParameters(**native, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virTypedParameterPtr params = static_cast<virTypedParameterPtr>(calloc(nparams, sizeof(virTypedParameter)));

    if (0 != virNodeGetMemoryParameters(**native, params, &nparams, 0)) {
        throwVirtError(isolate);
    } else {
        v8::Local<v8::Array> result = v8::Array::New(isolate, nparams);

        for (int i = 0; i < nparams; i++) {
            virTypedParameterPtr param = params + i;
            v8::Local<v8::Object> item = v8::Object::New(isolate);

            item->Set(v8::String::NewFromUtf8(isolate, "type"), v8::Number::New(isolate, param->type));
            item->Set(v8::String::NewFromUtf8(isolate, "field"), v8::String::NewFromUtf8(isolate, param->field));

            switch (param->type) {
            case VIR_TYPED_PARAM_INT:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Number::New(isolate, param->value.i));
                break;
            case VIR_TYPED_PARAM_UINT:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Number::New(isolate, param->value.ui));
                break;
            case VIR_TYPED_PARAM_LLONG:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Number::New(isolate, param->value.l));
                break;
            case VIR_TYPED_PARAM_ULLONG:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Number::New(isolate, param->value.ul));
                break;
            case VIR_TYPED_PARAM_DOUBLE:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Number::New(isolate, param->value.d));
                break;
            case VIR_TYPED_PARAM_BOOLEAN:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::Boolean::New(isolate, 0 != param->value.b));
                break;
            case VIR_TYPED_PARAM_STRING:
                item->Set(v8::String::NewFromUtf8(isolate, "value"), v8::String::NewFromUtf8(isolate, param->value.s));
                break;
            }

            result->Set(i, item);
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int cellNum = args[1]->Int32Value();    
    int nparams = 0;

    if (0 != virNodeGetMemoryStats(**native, cellNum, NULL, &nparams, 0)) {
        throwVirtError(isolate);
        return;
    }

    if (nparams <= 0) {
        args.GetReturnValue().Set(v8::Object::New(isolate));
        return;
    }

    virNodeMemoryStatsPtr params = static_cast<virNodeMemoryStatsPtr>(calloc(nparams, sizeof(virNodeMemoryStats)));

    if (0 != virNodeGetMemoryStats(**native, cellNum, params, &nparams, 0)) {
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
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virSecurityModel secmodel;
    memset(&secmodel, 0, sizeof(virSecurityModel));
    if (0 != virNodeGetSecurityModel(**native, &secmodel)) {
        throwVirtError(isolate);
        return;
    }

    v8::Local<v8::Object> result = v8::Object::New(isolate);
    result->Set(v8::String::NewFromUtf8(isolate, "model"), v8::String::NewFromUtf8(isolate, secmodel.model));
    result->Set(v8::String::NewFromUtf8(isolate, "doi"), v8::String::NewFromUtf8(isolate, secmodel.doi));
    args.GetReturnValue().Set(result);
}

static void __virNodeSetMemoryParameters(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 2);
    CHK_ARGUMENT_TYPE(isolate, args[1], Array);
    v8::Local<v8::Array> arg1 = v8::Local<v8::Array>::Cast(args[1]);
    v8::Local<v8::String> propField = v8::String::NewFromUtf8(isolate, "field");
    v8::Local<v8::String> propType = v8::String::NewFromUtf8(isolate, "type");
    v8::Local<v8::String> propValue = v8::String::NewFromUtf8(isolate, "value");
    int nparams = arg1->Length();
    for (int i = 0; i < nparams; i++) {
        v8::Local<v8::Value> item = arg1->Get(i);
        CHK_ARGUMENT_TYPE(isolate, item, Object);
        v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(item);

        if (!obj->Has(propField)) {
            throwTypeError(isolate, "Property `field` not found");
            return;
        }

        if (!obj->Get(propField)->IsString()) {
            throwTypeError(isolate, "Property `field` was supposed to be string");
            return;
        }

        if (!obj->Has(propType)) {
            throwTypeError(isolate, "Property `type` not found");
            return;
        }

        if (!obj->Get(propType)->IsInt32()) {
            throwTypeError(isolate, "Property `type` was supposed to be integer");
            return;
        }

        if (!obj->Has(propValue)) {
            throwTypeError(isolate, "Property `value` not found");
            return;
        }
    }
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    virTypedParameterPtr params = static_cast<virTypedParameterPtr>(calloc(nparams, sizeof(virTypedParameter)));

    for (int i = 0; i < nparams; i++) {
        v8::Local<v8::Object> item = v8::Local<v8::Object>::Cast(arg1->Get(i));
        virTypedParameterPtr param = params + i;

        // field
        v8::String::Utf8Value field(item->Get(propField)->ToString());
        memcpy(param->field, *field, VIR_TYPED_PARAM_FIELD_LENGTH * sizeof(char));

        // type
        param->type = item->Get(propType)->Int32Value();

        // value
        switch (param->type) {
        case VIR_TYPED_PARAM_INT:
            param->value.i = item->Get(propValue)->Int32Value();
            break;
        case VIR_TYPED_PARAM_UINT:
            param->value.ui = item->Get(propValue)->Uint32Value();
            break;
        case VIR_TYPED_PARAM_LLONG:
            param->value.l = item->Get(propValue)->IntegerValue();
            break;
        case VIR_TYPED_PARAM_ULLONG:
            param->value.ul = item->Get(propValue)->IntegerValue() & 0xffffffffffffffffL;
            break;
        case VIR_TYPED_PARAM_DOUBLE:
            param->value.d = item->Get(propValue)->NumberValue();
            break;
        case VIR_TYPED_PARAM_BOOLEAN:
            param->value.b = item->Get(propValue)->BooleanValue() ? 1 : 0;
            break;
        case VIR_TYPED_PARAM_STRING: {
                v8::String::Utf8Value value(item->Get(propValue)->ToString());
                param->value.s = strdup(*value);
            }
            break;
        }
    }

    if (0 != virNodeSetMemoryParameters(**native, params, nparams, 0)) {
        throwVirtError(isolate);
    }

    for (int i = 0; i < nparams; i++) {
        virTypedParameterPtr param = params + i;

        if (VIR_TYPED_PARAM_STRING == param->type && NULL != param->value.s) {
            free(param->value.s);
        }
    }

    free(params);
}

static void __virNodeSuspendForDuration(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);
    CHK_ARGUMENT_TYPE(isolate, args[1], Uint32);
    CHK_ARGUMENT_TYPE(isolate, args[2], Uint32);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    unsigned int target = args[1]->Uint32Value();
    unsigned long long duration = args[2]->IntegerValue();
    if (0 != virNodeSuspendForDuration(**native, target, duration, 0)) {
        throwVirtError(isolate);
    }
}

static void __virConnectListInterfaces(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 1);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    Connection *native = node::ObjectWrap::Unwrap<Connection>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);

    int max = virConnectNumOfDefinedInterfaces(**native);
    if (-1 == max) {
        throwVirtError(isolate);
        return;
    }

    char **names = static_cast<char**>(calloc(max, sizeof(void*)));
    int niface = virConnectListInterfaces(**native, names, max);
    if (-1 == niface) {
        throwVirtError(isolate);
        return;
    }

    v8::Local<v8::Array> result = v8::Array::New(isolate, niface);
    for (int i = 0; i < niface; i++) {
        result->Set(i, v8::String::NewFromUtf8(isolate, names[i]));
    }

    args.GetReturnValue().Set(result);
}


void initialize(v8::Handle<v8::Object> exports) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();

    if (0 != virInitialize()) {
        throwVirtError(isolate);
        return;
    }

    Connection::Export<Connection>(exports, "Connection");
    Domain::Export<Domain>(exports, "Domain");
    Interface::Export<Interface>(exports, "Interface");

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
    NODE_SET_METHOD(exports, "virNodeSetMemoryParameters", __virNodeSetMemoryParameters);
    NODE_SET_METHOD(exports, "virNodeSuspendForDuration",  __virNodeSuspendForDuration);
    NODE_SET_METHOD(exports, "virConnectListInterfaces",   __virConnectListInterfaces);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, initialize)
