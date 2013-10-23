var virt = require('../');

var conn = virt.virConnectOpen('qemu:///system');

if (conn) {
    console.log('Connection: ' + conn);
    console.log('Connection hostname: ' + virt.virConnectGetHostname(conn));
    console.log('Connection Max Vcpus: ' + virt.virConnectGetMaxVcpus(conn));
    console.log('Connection version: ' + virt.virConnectGetVersion(conn));
    console.log('Connection lib version: ' + virt.virConnectGetLibVersion(conn));
    console.log('node free memory: ' + virt.virNodeGetFreeMemory(conn));
    console.log('node info: ' + JSON.stringify(virt.virNodeGetInfo(conn)));

    virt.virConnectClose(conn);
}

