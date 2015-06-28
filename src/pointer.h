#ifndef __POINTER_H__
#define __POINTER_H__

#include <node.h>
#include <node_object_wrap.h>

#include "virt-error.h"

#define TRACE() printf("%s#%d\n", __FUNCTION__, __LINE__)

#define CHK_NATIVE_CLASS_FUNCTION_ARGUMENTS(args, isolate, argc) \
    do {                                                         \
        if ((args).Length() < (argc)) {                          \
            virt::throwError((isolate), "Too few arguments");    \
            return;                                              \
        }                                                        \
                                                                 \
        if (!(args)[0]->IsObject()) {                            \
            virt::throwTypeError((isolate), "Invalid arguments");\
            return;                                              \
        }                                                        \
    } while (0);

#define CHK_NATIVE_CLASS_INSTANCE_ACCESSIBILITY(isolate, native) \
    do {                                                         \
        if (NULL == (native)) {                                  \
            virt::throwError((isolate), "Invalid arguments");    \
            return;                                              \
        }                                                        \
                                                                 \
        if ((native)->IsNull()) {                                \
            return;                                              \
        }                                                        \
    } while (0);

#define CHK_ARGUMENT_TYPE(isolate, arg, type)                    \
    do {                                                         \
        if (!arg->Is ## type()) {                                \
            virt::throwTypeError(isolate, "Invalid arguments");  \
            return;                                              \
        }                                                        \
    } while (0);

template <typename T>
class Pointer : public node::ObjectWrap {
public:

    template<class S>
    inline static void Export(v8::Handle<v8::Object> exports, const char *clazz) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Pointer<T>::New<S>);
        tpl->SetClassName(v8::String::NewFromUtf8(isolate, clazz));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::Function> ctor = tpl->GetFunction();
        S::constructor.Reset(isolate, ctor);
        exports->Set(v8::String::NewFromUtf8(isolate, clazz), ctor);
    }

    template <typename S>
    inline static void NewInstance(T t, const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);
        v8::Handle<v8::Value> argv[] = { v8::External::New(isolate, t) };
        v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, S::constructor);
        args.GetReturnValue().Set(ctor->NewInstance(1, argv));
    }

    template <typename S>
    inline static v8::Local<v8::Object> NewInstance(T t) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::Handle<v8::Value> argv[] = { v8::External::New(isolate, t) };
        v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, S::constructor);
        return ctor->NewInstance(1, argv);
    }

    inline Pointer(T t = NULL) : ptr(t) { }

    inline T operator*() const { return this->ptr; }

    inline T operator->() const { return this->ptr; }

    template <class S>
    inline bool operator==(const Pointer<S>& that) const {
        return this->ptr == that.ptr;
    }

    template <class S>
    inline bool operator!=(const Pointer<S>& that) const {
        return !operator==(that);
    }

    inline bool IsNull() const { return NULL == this->ptr; }

    inline void SetNull() { this->ptr = NULL; }

private:

    template <class S>
    inline static void New(const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);

        if (args.IsConstructCall()) {
            if (!args[0]->IsExternal()) {
                virt::throwError(isolate, "Unsupported operation");
                return;
            }

            S *ptr = new S(static_cast<T>(v8::External::Cast(*args[0])->Value()));
            ptr->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            v8::Local<v8::Value> argv[] = { args[0] };
            v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, S::constructor);
            args.GetReturnValue().Set(ctor->NewInstance(1, argv));
        }
    }

    T ptr;
};

#endif /* __POINTER_H__ */
