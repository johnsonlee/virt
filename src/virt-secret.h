#ifndef __NODE_VIRT_SECRET_H__
#define __NODE_VIRT_SECRET_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virSecretPtr>;

namespace virt {
    namespace secret {

        void exports(v8::Handle<v8::Object> exports);

        class Secret : public Pointer<virSecretPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Secret(virSecretPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virSecretPtr>;
        };

    } // namespace secret
} // namespace virt

#endif /* __NODE_VIRT_SECRET_H__ */
