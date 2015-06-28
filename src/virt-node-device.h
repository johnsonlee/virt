#ifndef __NODE_VIRT_NODE_DEVICE_H__
#define __NODE_VIRT_NODE_DEVICE_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virNodeDevicePtr>;

namespace virt {
    namespace nodedev {

        void exports(v8::Handle<v8::Object> exports);

        class NodeDevice : public Pointer<virNodeDevicePtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline NodeDevice(virNodeDevicePtr ptr) : Pointer(ptr) {}

            friend class Pointer<virNodeDevicePtr>;
        };

    } // namespace nodedev
} // namespace virt

#endif /* __NODE_VIRT_NODE_DEVICE_H__ */
