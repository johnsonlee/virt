#ifndef __NODE_VIRT_NETWORK_H__
#define __NODE_VIRT_NETWORK_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virNetworkPtr>;

namespace virt {
    namespace network {

        void exports(v8::Handle<v8::Object> exports);

        class Network : public Pointer<virNetworkPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Network(virNetworkPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virNetworkPtr>;
        };

    } // namespace network
} // namespace virt

#endif /* __NODE_VIRT_NETWORK_H__ */
