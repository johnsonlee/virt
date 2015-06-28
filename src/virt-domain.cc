// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-domain.h"

#ifdef __cplusplus
extern "C" {
#endif

static void __virConnectDomainEventRegister(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, 3);
    CHK_ARGUMENT_TYPE(isolate, args[1], Function);
    v8::Local<v8::Object> holder = v8::Local<v8::Object>::Cast(args[0]);
    virt::domain::Domain *native = node::ObjectWrap::Unwrap<virt::domain::Domain>(holder);
    CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native);
    // FIXME
}

static void __virConnectDomainEventDeregister(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    // FIXME
    virt::throwError(isolate, "Unimplemented");
}

static void __virConnectDomainEventDeregisterAny(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    // FIXME
    virt::throwError(isolate, "Unimplemented");
}

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace domain {

        v8::Persistent<v8::Function> Domain::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            Domain::Export<Domain>(exports, "Domain");

            NODE_SET_METHOD(exports, "virConnectDomainEventRegister",       __virConnectDomainEventRegister);
            NODE_SET_METHOD(exports, "virConnectDomainEventDeregister",     __virConnectDomainEventDeregister);
            NODE_SET_METHOD(exports, "virConnectDomainEventDeregisterAny",  __virConnectDomainEventDeregisterAny);
        }

    } // namespace domain
} // namespace virt

