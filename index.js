var libvirt = require('./build/Release/virt.node');

/**
 * Virtual node
 */
var VirtualNode = function() {
};

/**
 * Free memory
 * 
 * @type {@link Number}
 */
VirtualNode.prototype.__defineGetter__('freeMemory', function() {
    return libvirt.virNodeGetFreeMemory(this.id);
});

/**
 * Detail information
 *   - model    String indicate the CPU model
 *   - memory   Memory size in kilobytes
 *   - cpus     The number of active CPUs
 *   - mhz      Expected CPU frequency
 *   - nodes    The number of NUMA nodes, 1 for uniform memory access
 *   - sockets  Number of CPU sockets per node
 *   - cores    Number of cores per socket
 *   - threads  Number of threads per core
 */
VirtualNode.prototype.__defineGetter__('info', function() {
    return libvirt.virNodeGetInfo(this.id);
});


/**
 * Virtual connection
 */
var VirtualConnection = function() {
    this.id = 0;
};

/**
 * Extends from {@link VirtualNode}
 */
VirtualConnection.prototype = Object.create(VirtualNode.prototype, {
    constructor : {
        value : VirtualConnection.prototype,
        configurable : true,
        enumerable : false,
        writable : true,
    },
});

VirtualConnection.prototype.open = function(uri) {
    if (this.id) {
        this.close();
    }

    this.id = libvirt.virConnectOpen(uri);
};

VirtualConnection.prototype.close = function() {
    libvirt.virConnectClose(this.id);
    this.id = null;
};

VirtualConnection.prototype.__defineGetter__('uri', function() {
    return libvirt.virConnectGetURI(this.id);
});

VirtualConnection.prototype.__defineGetter__('hostname', function() {
    return libvirt.virConnectGetHostname(this.id);
});

VirtualConnection.prototype.__defineGetter__('version', function() {
    return libvirt.virConnectGetVersion(this.id);
});

VirtualConnection.prototype.__defineGetter__('libVersion', function() {
    return libvirt.virConnectGetLibVersion(this.id);
});

VirtualConnection.prototype.__defineGetter__('maxVcpus', function() {
    return libvirt.virConnectGetMaxVcpus(this.id);
})

module.exports = VirtualConnection;

