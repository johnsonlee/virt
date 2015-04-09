#include "native-class.h"
#include "throw.h"

v8::Persistent<v8::Function> NativeClass::constructor;

NativeClass::NativeClass(void *ptr) : ptr_(ptr) {
}

NativeClass::~NativeClass() {
}

void NativeClass::Export(v8::Handle<v8::Object> exports, const char *clazz) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, NativeClass::New);
    tpl->SetClassName(v8::String::NewFromUtf8(isolate, clazz));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::Function> ctor = tpl->GetFunction();
    NativeClass::constructor.Reset(isolate, ctor);
    exports->Set(v8::String::NewFromUtf8(isolate, clazz), ctor);
}

void NativeClass::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    if (args.IsConstructCall()) {
        if (!args[0]->IsExternal()) {
            throwError(isolate, "Unsupported operation");
            return;
        }

        NativeClass *ptr = new NativeClass(v8::External::Cast(*args[0])->Value());
        ptr->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        v8::Local<v8::Value> argv[] = { args[0] };
        v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, NativeClass::constructor);
        args.GetReturnValue().Set(ctor->NewInstance(1, argv));
    }
}

void NativeClass::NewInstance(void *ptr, const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    v8::Handle<v8::Value> argv[] = { v8::External::New(isolate, ptr) };
    v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, NativeClass::constructor);
    args.GetReturnValue().Set(ctor->NewInstance(1, argv));
}

