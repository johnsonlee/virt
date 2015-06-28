#ifndef __NODE_VIRT_INTERFACE_H__
#define __NODE_VIRT_INTERFACE_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virInterfacePtr>;

namespace virt {
    namespace interface {

        void exports(v8::Handle<v8::Object> exports);

        class Interface : public Pointer<virInterfacePtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Interface(virInterfacePtr ptr) : Pointer(ptr) {}

            friend class Pointer<virInterfacePtr>;
        };

    } // namespace interface
} // namespace virt

#endif /* __NODE_VIRT_INTERFACE_H__ */
