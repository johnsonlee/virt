// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-storage.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace storage {

        v8::Persistent<v8::Function> StoragePool::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            StoragePool::Export<StoragePool>(exports, "StoragePool");
        }

    } // namespace storage
} // namespace virt

