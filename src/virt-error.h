#ifndef __NODE_VIRT_ERROR_H__
#define __NODE_VIRT_ERROR_H__

// node
#include <v8.h>

// libvirt
#include <libvirt/virterror.h>

namespace virt {

    inline void throwError(v8::Isolate *isolate, const char *msg) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, msg)));
    }

    inline void throwTypeError(v8::Isolate *isolate, const char *msg) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, msg)));
    }

    inline void throwVirtError(v8::Isolate *isolate) {
        const char *msg = virGetLastErrorMessage();
        throwError(isolate, (NULL == msg) ? "Unknown error" : msg);
    }

} // namespace virt

#endif /* __NODE_VIRT_ERROR_H__ */
