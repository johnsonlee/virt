#ifndef __NATIVE_CLASS_H__
#define __NATIVE_CLASS_H__

// node
#include <node.h>
#include <node_object_wrap.h>

class NativeClass : public node::ObjectWrap {
public:
    static void Export(v8::Handle<v8::Object> exports, const char *clazz);
    static void NewInstance(void *ptr, const v8::FunctionCallbackInfo<v8::Value>& args);

    inline void* operator*() const {
        return this->ptr_;
    }

    inline bool IsEmpty() const {
        return NULL == this->ptr_;
    }

    inline void Clear() {
        this->ptr_ = NULL;
    }

private:
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;

    explicit NativeClass(void *ptr = NULL);
    ~NativeClass();

    void* ptr_;
};

#endif /* __NATIVE_CLASS_H__ */
