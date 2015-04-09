#ifndef __CONNECTION_H__
#define __CONNECTION_H__

// node
#include <node.h>
#include <node_object_wrap.h>

// libvirt
#include <libvirt/libvirt.h>

namespace virt {

    class Connection : public node::ObjectWrap {
    public:
        static void Init(v8::Handle<v8::Object> exports);
        static void NewInstance(virConnectPtr conn, const v8::FunctionCallbackInfo<v8::Value>& args);

    private:
        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;

        explicit Connection(virConnectPtr conn = NULL);
        ~Connection();

        virConnectPtr connection;
    };

} // namespace virt

#endif /* __CONNECTION_H__ */
