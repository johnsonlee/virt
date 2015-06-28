#ifndef __NODE_VIRT_STREAM_H__
#define __NODE_VIRT_STREAM_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virStreamPtr>;

namespace virt {
    namespace stream {

        void exports(v8::Handle<v8::Object> exports);

        class Stream : public Pointer<virStreamPtr> {
        private:
            static v8::Persistent<v8::Function> constructor;

            inline Stream(virStreamPtr ptr) : Pointer(ptr) {}

            friend class Pointer<virStreamPtr>;
        };

    } // namespace stream
} // namespace virt

#endif /* __NODE_VIRT_STREAM_H__ */
