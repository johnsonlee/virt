/**
 * libvirt-secret for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-secret.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace secret {

        v8::Persistent<v8::Function> Secret::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            Secret::Export<Secret>(exports, "Secret");
        }

    } // namespace secret
} // namespace virt

