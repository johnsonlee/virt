#ifndef __NODE_VIRT_HOST_H__
#define __NODE_VIRT_HOST_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virConnectPtr>;

namespace virt {
    namespace host {

        void exports(v8::Handle<v8::Object> exports);

        class Connection : public Pointer<virConnectPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Connection(virConnectPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virConnectPtr>;
        };

    } // namespace host
} // namespace virt

#endif /* __NODE_VIRT_HOST_H__ */
