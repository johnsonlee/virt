/**
 * libvirt-nwfilter for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-network-filter.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace nwfilter {

        v8::Persistent<v8::Function> NetworkFilter::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            NetworkFilter::Export<NetworkFilter>(exports, "NetworkFilter");
        }

    } // namespace nwfilter
} // namespace virt

