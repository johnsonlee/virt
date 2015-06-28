#ifndef __NODE_VIRT_NETWORK_FILTER_H__
#define __NODE_VIRT_NETWORK_FILTER_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virNWFilterPtr>;

namespace virt {
    namespace nwfilter {

        void exports(v8::Handle<v8::Object> exports);

        class NetworkFilter : public Pointer<virNWFilterPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline NetworkFilter(virNWFilterPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virNWFilterPtr>;
        };

    } // namespace nwfilter
} // namespace virt

#endif /* __NODE_VIRT_NETWORK_FILTER_H__ */
