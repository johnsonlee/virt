#ifndef __NODE_VIRT_DOMAIN_H__
#define __NODE_VIRT_DOMAIN_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virDomainPtr>;

namespace virt {
    namespace domain {

        void exports(v8::Handle<v8::Object> exports);

        class Domain : public Pointer<virDomainPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Domain(virDomainPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virDomainPtr>;
        };

    } // namespace domain
} // namespace virt

#endif /* __NODE_VIRT_DOMAIN_H__ */
