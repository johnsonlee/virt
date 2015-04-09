#include "connection.h"
#include "throw.h"

namespace virt {

    v8::Persistent<v8::Function> Connection::constructor;

    Connection::Connection(virConnectPtr conn) : connection(conn) {
    }

    Connection::~Connection() {
    }

    void Connection::Init(v8::Handle<v8::Object> exports) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();

        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Connection::New);
        tpl->SetClassName(v8::String::NewFromUtf8(isolate, "Connection"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        v8::Local<v8::Function> ctor = tpl->GetFunction();
        Connection::constructor.Reset(isolate, ctor);
        exports->Set(v8::String::NewFromUtf8(isolate, "Connection"), ctor);
    }

    void Connection::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);

        if (args.IsConstructCall()) {
            if (!args[0]->IsExternal()) {
                throwError(isolate, "Unsupported operation");
                return;
            }

            virConnectPtr ptr = static_cast<virConnectPtr>(v8::External::Cast(*args[0])->Value());
            Connection *conn = new Connection(ptr);
            conn->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            v8::Local<v8::Value> argv[] = { args[0] };
            v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, Connection::constructor);
            args.GetReturnValue().Set(ctor->NewInstance(1, argv));
        }
    }

    void Connection::NewInstance(virConnectPtr conn, const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::HandleScope scope(isolate);
        v8::Handle<v8::Value> argv[] = { v8::External::New(isolate, conn) };
        v8::Local<v8::Function> ctor = v8::Local<v8::Function>::New(isolate, Connection::constructor);
        args.GetReturnValue().Set(ctor->NewInstance(1, argv));
    }

} // namespace virt
