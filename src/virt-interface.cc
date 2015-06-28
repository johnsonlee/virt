/**
 * libvirt-domain-snapshot for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-interface.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace interface {

        v8::Persistent<v8::Function> Interface::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            Interface::Export<Interface>(exports, "Interface");
        }

    } // namespace interface
} // namespace virt
