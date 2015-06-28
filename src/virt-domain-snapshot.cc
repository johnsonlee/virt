/**
 * libvirt-domain-snapshot for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

// standard c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "virt-domain-snapshot.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace virt {
    namespace domainsnapshot {

        v8::Persistent<v8::Function> DomainSnapshot::constructor;

        void exports(v8::Handle<v8::Object> exports) {
            DomainSnapshot::Export<DomainSnapshot>(exports, "DomainSnapshot");
        }

    } // namespace domainsnapshot
} // namespace virt

