#ifndef __THROW_H__
#define __THROW_H__

// node
#include <v8.h>

// libvirt
#include <libvirt/virterror.h>

static void throwError(v8::Isolate *isolate, const char *msg) {
    isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, msg)));
}

static void throwTypeError(v8::Isolate *isolate, const char *msg) {
    isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, msg)));
}

static void throwVirtError(v8::Isolate *isolate) {
    const char *msg = virGetLastErrorMessage();
    throwError(isolate, (NULL == msg) ? "Unknown error" : msg);
}

#endif /* __THROW_H__ */
