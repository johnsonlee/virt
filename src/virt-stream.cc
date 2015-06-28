/**
 * libvirt-stream for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-stream.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace stream {

        v8::Persistent<v8::Function> Stream::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            Stream::Export<Stream>(exports, "Stream");
        }

    } // namespace stream
} // namespace virt

