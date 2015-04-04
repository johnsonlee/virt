/**
 * {@link https://libvirt.org libvirt} API doc for Node
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 * @overview
 * @version 1.0.4
 */

var virt = require('./build/Release/virt.node');

/**
 * Hypervisor Connection
 * 
 * @class
 * @see {@link https://libvirt.org/html/libvirt-libvirt-host.html#virConnect}
 */
function Connection() {

    this.$name = null;

}

/**
 * <p>This function should be called first to get a connection to the
 * Hypervisor and xen store</p>
 * 
 * <p>If <code>name</code> is null or undefined, if the
 * <code>LIBVIRT_DEFAULT_URI</code> environment variable is set, then it
 * will be used. Otherwise if the client configuration file has the
 * "uri_default" parameter set, then it will be used. Finally probing will
 * be done to determine a suitable default driver to activate. This
 * involves trying each hypervisor in turn until one successfully opens.</p>
 * If connecting to an unprivileged hypervisor driver which requires the
 * libvirtd daemon to be active, it will automatically be launched if not
 * already running. This can be prevented by setting the environment
 * variable <code>LIBVIRT_AUTOSTART=0</code></p>
 * 
 * <p>URIs are documented at {@link http://libvirt.org/uri.html}</p>
 * 
 * <p>{@link Connection#close()} should be used to release the resources
 * after the connection is no longer needed.</p>
 * 
 * @param name {String}
 *        URI of the hypervisor, optional
 * @return {Connection} a hypervisor connection
 * @throws {Error}
 */
Connection.open = function() {
    return virt.virConnectOpen.apply(virt, arguments);
};

/**
 * <p>This function should be called first to get a connection to the
 * Hypervisor. If necessary, authentication will be performed fetching
 * credentials via the callback</p>
 * 
 * <p>See {@link Connection#open()} for notes about environment variables
 * which can have an effect on opening drivers and freeing the connection
 * resources</p>
 * 
 * <p>URIs are documented at {@link http://libvirt.org/uri.html}</p>
 * 
 * @param name {String}
 *        URI of the hypervisor, optional
 * @param auth {ConnectionAuth}
 *        authenticate callback parameters
 * @param flags {Number}
 *        bitwise-OR of virConnectFlags
 * @return {Connection} the hypervisor connection
 * @throws {Error}
 * @see VIR_CONNECT_RO
 * @see VIR_CONNECT_NO_ALIASES
 */
Connection.openAuth = function() {
    return virt.virConnectOpenAuth.apply(virt, arguments);
};

/**
 * <p>This function should be called first to get a restricted connection to
 * the library functionalities. The set of APIs usable are then restricted
 * on the available methods to control the domains.</p>
 * 
 * <p>See {@link Connection#open()} for notes about environment variables
 * which can have an effect on opening drivers and freeing the connection
 * resources</p>
 * 
 * <p>URIs are documented at {@link http://libvirt.org/uri.html}</p>
 * 
 * @param name {String}
 *        URI of the hypervisor, optional
 * @return {Connection} the hypervisor connection
 * @throws {Error}
 */
Connection.openReadOnly = function() {
    return virt.virConnectOpenReadOnly.apply(virt, arguments);
};

Connection.prototype = {

    /**
     * Registers a callback to be invoked when the connection event occurred
     * 
     * @param event {String}
     *        the name of event
     * @param listener {Function}
     *        the callback function
     */
    addEventListener : function(event, listener) {
        return virt.addEventListener.apply(virt, arguments);
    },

    /**
     * Unregisters the callback previously set with the
     * {@link Connection#addEventListener()}
     * 
     * @param event {String}
     *        the name of event
     * @param listener {Function}
     *        the callback function
     */
    removeEventListener : function(event, listener) {
        return virt.removeEventListener.apply(virt, arguments);
    },

    /**
     * Computes the most feature-rich CPU which is compatible with all given host CPUs.
     * 
     * @param xmlCPUs {Array}
     *        array of XML descriptions of host CPUs
     * @param flags {Number}
     *        bitwise-OR of virConnectBaselineCPUFlags
     * @return {String} XML description of the computed CPU (caller frees) or
     * {@code undefined} on error.
     * @see VIR_CONNECT_BASELINE_CPU_EXPAND_FEATURES
     * @see VIR_CONNECT_BASELINE_CPU_MIGRATABLE
     */
    baselineCPU : function() {
        return virt.virConnectBaselineCPU.apply(virt, args);
    },

    /**
     * This function closes the connection to the Hypervisor.
     * 
     * @return {Number} a positive number if at least 1 reference remains on
     * success. The returned value should not be assumed to be the total
     * reference count. A return of 0 implies no references remain and the
     * connection is closed and memory has been freed.
     */
    close : function() {
        return virt.virConnectClose.apply(virt, args);
    },

    /**
     * Compares the given CPU description with the host CPU
     * 
     * @param xmlDesc {String}
     *        XML describing the CPU to compare with host CPU
     * @param flags {Number}
     *        bitwise-OR of virConnectCompareCPUFlags
     * @return {Number} comparison result
     * @see VIR_CPU_COMPARE_ERROR
     * @see VIR_CPU_COMPARE_INCOMPATIBLE
     * @see VIR_CPU_COMPARE_IDENTICAL
     * @see VIR_CPU_COMPARE_SUPERSET
     * @see VIR_CPU_COMPARE_LAST
     */
    compareCPU : function() {
        return virt.virConnectCompareCPU.apply(virt, args);
    },

    /**
     * Get the list of supported CPU models for a specific architecture.
     * 
     * @param arch {String}
     *        architecture
     * @param models {Array}
     *        the CPU models supported for the specified architecture
     * @param flags {Number}
     *        extra flags; not used yet, so callers should always pass 0
     * @return {Number} -1 on error, number of elements in models on success
     */
    getCPUModelNames : function() {
        return virt.virConnectGetCPUModelNames.apply(virt, arguments);
    },

    /**
     * Get the capabilities of the hypervisor / driver.
     * 
     * @return {String} a XML string defining the capabilities.
     */
    getCapabilities : function() {
        return virt.virConnectGetCapabilities.apply(virt, arguments);
    },

    /**
     * This returns a system hostname on which the hypervisor is running
     * (based on the result of the gethostname system call, but possibly
     * expanded to a fully-qualified domain name via getaddrinfo). If we are
     * connected to a remote system, then this returns the hostname of the
     * remote system.
     * 
     * @param conn {Connection}
     *        hypervisor connection
     * @return {String} the hostname which must be freed by the caller
     * @throws {Error}
     */
    getHostname : function() {
        return virt.virConnectGetHostname.apply(virt, arguments);
    },

    /**
     * Returns the version of libvirt used by the daemon running on the host
     * 
     * @param conn {Connection}
     *        hypervisor connection
     * @return {Number} libvirt library version used on the connection
     * @throws {Error}
     */
    getLibVersion : function() {
        return virt.virConnectGetLibVersion.apply(virt, arguments);
    },

    /**
     * Provides the maximum number of virtual CPUs supported for a guest VM of
     * a specific type. The 'type' parameter here corresponds to the 'type'
     * attribute in the <domain> element of the XML
     * 
     * @param type {String}
     *        value of the 'type' attribute in the <domain> element
     * @return {Number} the maximum of virtual CPU
     * @throws {Error}
     */
    getMaxVcpus : function() {
        return virt.virConnectGetMaxVcpus.apply(virt, arguments);
    },

    /**
     * This returns the XML description of the sysinfo details for the host on
     * which the hypervisor is running, in the same format as the <sysinfo>
     * element of a domain XML. This information is generally available only
     * for hypervisors running with root privileges.
     * 
     * @param flags {Number}
     * @return {String} the XML string
     * @throws {Error}
     */
    getSysinfo : function() {
        return virt.virConnectGetSysinfo.apply(virt, arguments);
    },

    /**
     * Get the name of the Hypervisor driver used. This is merely the driver
     * name; for example, both KVM and QEMU guests are serviced by the driver
     * for the qemu:// URI, so a return of "QEMU" does not indicate whether
     * KVM acceleration is present. For more details about the hypervisor, use
     * {@link virConnectGetCapabilities}
     * 
     * @return {String} the name of the Hypervisor driver used
     * @throws {Error}
     */
    getType : function() {
        return virt.virConnectGetType.apply(virt, arguments);
    },

    /**
     * This returns the URI (name) of the hypervisor connection. Normally this
     * is the same as or similar to the string passed to the
     * {@link Connection#open()} / {@link virConnectOpenReadOnly} call, but the
     * driver may make the URI canonical. If name is <code>null</code> was
     * passed to {@link Connection#open()}, then the driver will return a non-NULL
     * URI which can be used to connect to the same hypervisor later.
     * 
     * @return {String} the URI string
     * @throws {Error}
     */
    getURI : function() {
        return virt.virConnectGetURI.apply(virt, arguments);
    },

    /**
     * Get the version level of the Hypervisor running. This may work only with
     * hypervisor call, i.e. with privileged access to the hypervisor, not with
     * a Read-Only connection.
     * 
     * @return {Number} the version of the running hypervisor
     * @throws {Error}
     */
    getVersion : function() {
        return virt.virConnectGetVersion.apply(virt, arguments);
    },

    /**
     * Determine if the connection to the hypervisor is still alive
     * 
     * @return {Boolean} true if alive, false if dead
     */
    isAlive : function() {
        return virt.virConnectIsAlive.apply(virt, arguments);
    },

    /**
     * Determine if the connection to the hypervisor is encrypted
     * 
     * @return {Boolean} true if encrypted, false if not encrypted
     */
    isEncrypted : function() {
        return virt.virConnectIsEncrypted.apply(virt, arguments);
    },

    /**
     * Determine if the connection to the hypervisor is secure
     * 
     * @return {Boolean} true if secure, false if not secure
     */
    isSecure : function() {
        return virt.virConnectIsSecure.apply(virt, arguments);
    },

    /**
     * <p>Increment the reference count on the connection. For each additional
     * call to this method, there shall be a corresponding call to
     * {@link Connection#close()} to release the reference count, once the caller
     * no longer needs the reference to this object.</p>
     * 
     * <p>This method is typically useful for applications where multiple
     * threads are using a connection, and it is required that the connection
     * remain open until all threads have finished using it. ie, each new
     * thread using a connection would increment the reference count.</p>
     * 
     * @throws {Error}
     */
    ref : function() {
        return virt.virConnectRef.apply(virt, arguments);
    },

    /**
     * Start sending keepalive messages after <code>interval</code> seconds of
     * inactivity and consider the connection to be broken when no response is
     * received after <code>count</code> keepalive messages sent in a row. In
     * other words, sending <code>count + 1</code> keepalive message results in
     * closing the connection. When <code>interval</code> is <= 0, no keepalive
     * messages will be sent. When <code>count</code> is 0, the connection will
     * be automatically closed after <code>interval</code> seconds of
     * inactivity without sending any keepalive messages.
     * 
     * @param interval {Number}
     *        number of seconds of inactivity before a keepalive message is sent
     * @param count {Number}
     *        number of messages that can be sent in a row
     * @return {Boolean} true on success, false when remote party doesn't
     * support keepalive messages
     * @throws {Error}
     */
    setKeepAlive : function() {
        return virt.virConnectSetKeepAlive.apply(virt, arguments);
    },

    /**
     * Sometimes, when trying to start a new domain, it may be necessary to
     * reserve some huge pages in the system pool which can be then allocated
     * by the domain. This API serves that purpose.
     * 
     * @param allocations {Array}
     *        An array of {@link PageAllocation}
     * @param startCell {Number}
     *        index of first cell to allocate pages on
     * @param cellCount {Number}
     *        number of consecutive cells to allocate pages on
     * @param flags {Number}
     *        extra flags; binary-OR of virNodeAllocPagesFlags
     * @return the number of nodes successfully adjusted
     * @throws {Error}
     */
    nodeAllocPages : function(allocations, startCell, cellCount, flags) {
        return virt.virNodeAllocPages.apply(virt, arguments);
    },

    /**
     * Get CPU map of host node CPUs
     * 
     * @return {Array} CPUs present on the host node
     */
    nodeGetCPUMap : function() {
        return virt.virNodeGetCPUMap.apply(virt, arguments);
    },

    /**
     * This function provides individual cpu statistics of the node. If you
     * want to get total cpu statistics of the node, you must specify
     * {@link VIR_NODE_CPU_STATS_ALL_CPUS} to <code>cpuNum</code>.
     * 
     * @param cpuNum {Number}
     *        number of node cpu
     * @param params {Array}
     *        an Array of {@link NodeCPUStats}
     */
    nodeGetCPUStats : function() {
        return virt.virNodeGetCPUStats.apply(virt, arguments);
    },

    /**
     * Returns the free memory in one or more NUMA cells
     * 
     * @param startCell {Number}
     *        index of first cell
     * @return the free memory
     * @throws {Error}
     */
    nodeGetCellsFreeMemory : function(startCell) {
        return virt.virNodeGetCellsFreeMemory.apply(virt, arguments);
    },

    /**
     * Returns the free memory available on the Node
     * 
     * @return the available free memory in bytes
     * @throws {Error}
     */
    nodeGetFreeMemory : function() {
        return virt.virNodeGetFreeMemory.apply(virt, arguments);
    },

    /**
     * Queries the host system on free pages of specified size
     * 
     * @param pages {Array}
     *        page sizes to query
     * @param startCell {Number}
     *        index of first cell
     * @param cellCount {Number}
     *        maximum number of cells
     * @return {PageAllocation} the free pages
     * @throws {Error}
     */
    nodeGetFreePages : function(startCell, cellCount) {
        return virt.virNodeGetFreePages.apply(virt, arguments);
    },

    /**
     * Extract hardware information about the node.
     * 
     * @return {NodeInfo}
     * @throws {Error}
     */
    nodeGetInfo : function() {
        return virt.virNodeGetInfo.apply(virt, arguments);
    },

    /**
     * Get all node memory parameters (parameters unsupported by OS will be
     * omitted)
     * 
     * @return {TypedParameter}
     */
    nodeGetMemoryParameters : function() {
        return virt.virNodeGetMemoryParameters.apply(virt, arguments);
    },

};

for (var i in Connection.prototype) {
    var m = Connection.prototype[i];

    if ('function' === typeof m)
        continue;

    Connection.prototype[i] = function() {
        var args = Array.prototype.slice(arguments);
        args.unshift(this);
        m.apply(this, args);
    };
}

/**
 * @see {@link https://libvirt.org/html/libvirt-libvirt-host.html#virConnectAuth}
 * @class
 */
function ConnectionAuth() {

    /**
     * @type {Array}
     */
    this.credtypes = null;

    /**
     * @type {Function}
     */
    this.callback = null;

    /**
     * @type {Object}
     */
    this.userdata = null;

}

/**
 * Node cpu time parameter
 * 
 * @class
 */
function NodeCPUStats() {

    /**
     * @type {String}
     */
    this.field = null;

    /**
     * @type {Number}
     */
    this.value = 0;

}

/**
 * Node information
 * 
 * @class
 */
function NodeInfo() {

    /**
     * the CPU model
     * 
     * @type {String}
     */
    this.model = null;

    /**
     * memory size in kilobytes
     * @type {Number}
     */
    this.memory = 0;

    /**
     * the number of active CPUs
     * @type {Number}
     */
    this.cpus = 0;

    /**
     * expected CPU frequency
     * @type {Number}
     */
    this.mhz = 0;

    /**
     * the number of NUMA cell, 1 for unusual NUMA topologies or uniform memory
     * access; check capabilities XML for the actual NUMA topology
     * @type {Number}
     */
    this.nodes = 0;

    /**
     * number of CPU sockets per node if nodes > 1, 1 in case of unusual NUMA
     * topology
     * @type {Number}
     */
    this.sockets = 0;

    /**
     * number of cores per socket, total number of processors in case of
     * unusual NUMA topolog
     * @type {Number}
     */
    this.cores = 0;

    /**
     * number of threads per core, 1 in case of unusual numa topology
     * @type {Number}
     */
    this.threads = 0;

}

/**
 * Page allocation
 * 
 * @class
 */
function PageAllocation() {

    /**
     * which huge page size to allocate
     * @type {Number}
     */
    this.pageSize = 0;

    /**
     * how many pages should be allocated
     * @type {Number}
     */
    this.pageCount = 0;

}

/**
 * Typed parameter
 * 
 * @class
 */
function TypedParameter() {

    /**
     * The parameter name
     * @type {String}
     */
    this.field = null;

    /**
     * The parameter type
     * @type {Number}
     * @see VIR_TYPED_PARAM_INT
     * @see VIR_TYPED_PARAM_UINT
     * @see VIR_TYPED_PARAM_LLONG
     * @see VIR_TYPED_PARAM_ULLONG
     * @see VIR_TYPED_PARAM_DOUBLE
     * @see VIR_TYPED_PARAM_BOOLEAN
     * @see VIR_TYPED_PARAM_STRING
     */
    this.type = 0;

    /**
     * The parameter value
     * @type {Number|Boolean|String}
     */
    this.value = null;

}

(function() {

    /**
     * show all features
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CONNECT_BASELINE_CPU_EXPAND_FEATURES}
     */
    this.VIR_CONNECT_BASELINE_CPU_EXPAND_FEATURES = 1;

    /**
     * filter out non-migratable features
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CONNECT_BASELINE_CPU_MIGRATABLE}
     */
    this.VIR_CONNECT_BASELINE_CPU_MIGRATABLE = 2;


    /**
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CPU_COMPARE_ERROR}
     */
    this.VIR_CPU_COMPARE_ERROR = -1;

    /**
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CPU_COMPARE_INCOMPATIBLE}
     */
    this.VIR_CPU_COMPARE_INCOMPATIBLE = 0;

    /**
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CPU_COMPARE_IDENTICAL}
     */
    this.VIR_CPU_COMPARE_IDENTICAL = 1;

    /**
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CPU_COMPARE_SUPERSET}
     */
    this.VIR_CPU_COMPARE_SUPERSET = 2;

    /**
     *
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CPU_COMPARE_LAST}
     */
    this.VIR_CPU_COMPARE_LAST = 3;

    /**
     * A readonly connection
     * 
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CONNECT_RO}
     */
    this.VIR_CONNECT_RO = 1;

    /**
     * Don't try to resolve URI aliases
     * 
     * @see {@link http://libvirt.org/html/libvirt-libvirt-host.html#VIR_CONNECT_NO_ALIASES}
     */
    this.VIR_CONNECT_NO_ALIASES= 2;

    /**
     * Provides version information.
     * @return {String} the library version
     * @throws {Error}
     */
    this.getVersion = function() {
        return virt.virGetVersion.apply(virt, arguments);
    };

    this.Connection = Connection;

}).call(module.exports);

