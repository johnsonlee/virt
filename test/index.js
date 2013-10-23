var virt = require('../');

var conn = virt.virConnectOpenAuth('qemu:///system', {
        credtypes : [1, 2],
        callback : function(credentials, userdata) {
            console.log(userdata);
        },
        userdata : 'helloworld',
}, 1);

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

