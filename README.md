# virt

This package is a wrapper of libvirt for node js.

## Overview

The wrappered API is almost the same as libvirt, about libvirt, please see:

 * API Reference: http://libvirt.org/html/libvirt-libvirt.html
 * Development Guide: http://libvirt.org/devguide.html

## Dependencies

- libvirt
- node.js v0.10.x or higher

## Example

```
var Connection = require('virt').Connection;

var conn = Connection.open('vbox:///session');

try {
    var capabilities = conn.getCapabilities();
    console.log(capabilities);

    var hostname = conn.getHostname();
    console.log(hostname);

    ver libVersion = conn.getLibVersion();
    console.log(libVersion);

    var nodeInfo = conn.getNodeInfo();
    console.log(JSON.stringify(nodeInfo));
} catch (e) {
    console.log(e.stack);
} finally {
    if (conn) {
        conn.close();
    }
}
```

## libvirt API implementation matrix

| Libvirt API                                 | Implemented |
|:--------------------------------------------|:-----------:|
| virConnectBaselineCPU                       |      ✓      |
| virConnectClose                             |      ✓      |
| virConnectCompareCPU                        |      ✓      |
| virConnectDomainEventDeregister             |             |
| virConnectDomainEventDeregisterAny          |             |
| virConnectDomainEventRegister               |             |
| virConnectDomainEventRegisterAny            |             |
| virConnectDomainQemuMonitorEventDeregister  |             |
| virConnectDomainQemuMonitorEventRegister    |             |
| virConnectDomainXMLFromNative               |             |
| virConnectDomainXMLToNative                 |             |
| virConnectGetAllDomainStats                 |             |
| virConnectGetCPUModelNames                  |             |
| virConnectGetCapabilities                   |      ✓      |
| virConnectGetDomainCapabilities             |      ✓      |
| virConnectGetHostname                       |      ✓      |
| virConnectGetLibVersion                     |      ✓      |
| virConnectGetMaxVcpus                       |      ✓      |
| virConnectGetSysinfo                        |      ✓      |
| virConnectGetType                           |      ✓      |
| virConnectGetVersion                        |      ✓      |
| virConnectIsAlive                           |      ✓      |
| virConnectIsEncrypted                       |      ✓      |
| virConnectIsSecure                          |      ✓      |
| virConnectListAllDomains                    |             |
| virConnectListDefinedDomains                |             |
| virConnectListDomains                       |             |
| virConnectNumOfDefinedDomains               |             |
| virConnectNumOfDomains                      |             |
| virConnectOpen                              |      ✓      |
| virConnectOpenAuth                          |             |
| virConnectOpenReadOnly                      |      ✓      |
| virConnectSetKeepAlive                      |      ✓      |
| virConnectSupportsFeature                   |             |
| virDomainAbortJob                           |             |
| virDomainAddIOThread                        |             |
| virDomainAttachDevice                       |             |
| virDomainAttachDeviceFlags                  |             |
| virDomainBlockCommit                        |             |
| virDomainBlockCopy                          |             |
| virDomainBlockJobAbort                      |             |
| virDomainBlockJobSetSpeed                   |             |
| virDomainBlockPeek                          |             |
| virDomainBlockPull                          |             |
| virDomainBlockRebase                        |             |
| virDomainBlockResize                        |             |
| virDomainBlockStats                         |             |
| virDomainBlockStatsFlags                    |             |
| virDomainCoreDump                           |             |
| virDomainCoreDumpWithFormat                 |             |
| virDomainCreate                             |             |
| virDomainCreateLinux                        |             |
| virDomainCreateWithFiles                    |             |
| virDomainCreateWithFlags                    |             |
| virDomainCreateXML                          |             |
| virDomainCreateXMLWithFiles                 |             |
| virDomainDefineXML                          |             |
| virDomainDefineXMLFlags                     |             |
| virDomainDelIOThread                        |             |
| virDomainDestroy                            |             |
| virDomainDestroyFlags                       |             |
| virDomainDetachDevice                       |             |
| virDomainDetachDeviceFlags                  |             |
| virDomainFSFreeze                           |             |
| virDomainFSThaw                             |             |
| virDomainFSTrim                             |             |
| virDomainGetAutostart                       |             |
| virDomainGetBlkioParameters                 |             |
| virDomainGetBlockInfo                       |             |
| virDomainGetBlockIoTune                     |             |
| virDomainGetBlockJobInfo                    |             |
| virDomainGetCPUStats                        |             |
| virDomainGetControlInfo                     |             |
| virDomainGetDiskErrors                      |             |
| virDomainGetEmulatorPinInfo                 |             |
| virDomainGetFSInfo                          |             |
| virDomainGetHostname                        |             |
| virDomainGetIOThreadInfo                    |             |
| virDomainGetInfo                            |             |
| virDomainGetInterfaceParameters             |             |
| virDomainGetJobInfo                         |             |
| virDomainGetJobStats                        |             |
| virDomainGetMaxMemory                       |             |
| virDomainGetMaxVcpus                        |             |
| virDomainGetMemoryParameters                |             |
| virDomainGetMetadata                        |             |
| virDomainGetNumaParameters                  |             |
| virDomainGetOSType                          |             |
| virDomainGetSchedulerParameters             |             |
| virDomainGetSchedulerParametersFlags        |             |
| virDomainGetSchedulerType                   |             |
| virDomainGetSecurityLabel                   |             |
| virDomainGetSecurityLabelList               |             |
| virDomainGetState                           |             |
| virDomainGetTime                            |             |
| virDomainGetVcpuPinInfo                     |             |
| virDomainGetVcpus                           |             |
| virDomainGetVcpusFlags                      |             |
| virDomainGetXMLDesc                         |             |
| virDomainHasCurrentSnapshot                 |             |
| virDomainHasManagedSaveImage                |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |
|                                             |             |




## References

Please see [API References](https://rawgit.com/johnsonlee/virt/master/doc/index.html).

## License

Copyright (c) 2013-2015, Johnson Lee (MIT License).

