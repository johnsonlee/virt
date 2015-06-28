/**
 * libvirt-nodedev for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-node-device.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace nodedev {

        v8::Persistent<v8::Function> NodeDevice::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            NodeDevice::Export<NodeDevice>(exports, "NodeDevice");
        }

    } // namespace nodedev
} // namespace virt

