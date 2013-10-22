var VirtualConnction = require('../');

var conn = new VirtualConnction();

try {
    conn.open('qemu:///system');
    console.log('Connection id: ' + conn.id);
    console.log('Connection hostname: ' + conn.hostname);
    console.log('Connection Max Vcpus: ' + conn.maxVcpus);
    console.log('Connection version: ' + conn.version);
    console.log('Connection lib version: ' + conn.libVersion);
    console.log('node free memory: ' + conn.freeMemory);
    console.log('node info: ' + JSON.stringify(conn.info));
} catch (e) {
    console.error(e.stack);
} finally {
    conn.close();
}

