#ifndef __NODE_VIRT_DOMAIN_SNAPSHOT_H__
#define __NODE_VIRT_DOMAIN_SNAPSHOT_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virDomainSnapshotPtr>;

namespace virt {
    namespace domainsnapshot {

        void exports(v8::Handle<v8::Object> exports);

        class DomainSnapshot : public Pointer<virDomainSnapshotPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline DomainSnapshot(virDomainSnapshotPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virDomainSnapshotPtr>;
        };

    } // namespace domainsnapshot
} // namespace virt

#endif /* __NODE_VIRT_DOMAIN_SNAPSHOT_H__ */
