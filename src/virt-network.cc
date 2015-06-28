/**
 * libvirt-network for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-network.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace network {

        v8::Persistent<v8::Function> Network::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            Network::Export<Network>(exports, "Network");
        }

    } // namespace network
} // namespace virt

