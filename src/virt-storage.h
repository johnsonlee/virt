#ifndef __NODE_VIRT_STORAGE_H__
#define __NODE_VIRT_STORAGE_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virStoragePoolPtr>;

namespace virt {
    namespace storage {

        void exports(v8::Handle<v8::Object> exports);

        class StoragePool : public Pointer<virStoragePoolPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline StoragePool(virStoragePoolPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virStoragePoolPtr>;
        };

    } // namespace storage
} // namespace virt

#endif /* __NODE_VIRT_STORAGE_H__ */
