/**
 * libvirt for node js
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 */

#include <node.h>

#include "virt-domain.h"
#include "virt-domain-snapshot.h"
#include "virt-event.h"
#include "virt-host.h"
#include "virt-interface.h"
#include "virt-network.h"
#include "virt-node-device.h"
#include "virt-network-filter.h"
#include "virt-secret.h"
#include "virt-storage.h"
#include "virt-stream.h"

#ifdef __cplusplus
extern "C" {
#endif

void initialize(v8::Handle<v8::Object> exports) {
    v8::Isolate *isolate = v8::Isolate::GetCurrent();

    if (0 != virInitialize()) {
        virt::throwVirtError(isolate);
        return;
    }

    virt::domain::exports(exports);
    virt::domainsnapshot::exports(exports);
    virt::event::exports(exports);
    virt::host::exports(exports);
    virt::interface::exports(exports);
    virt::network::exports(exports);
    virt::nodedev::exports(exports);
    virt::nwfilter::exports(exports);
    virt::secret::exports(exports);
    virt::storage::exports(exports);
    virt::stream::exports(exports);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, initialize)

