/**
 * API reference for virt
 * 
 * @author Johnson Lee <g.johnsonlee@gmail.com>
 * @overview
 * @version 2.0.0
 */

var virt = require('./build/Release/virt.node');


/**
 * Hypervisor Connection
 * 
 * @class
 * @see {@link https://libvirt.org/html/libvirt-libvirt-host.html#virConnect}
 */
var Connection = virt.Connection;

/**
 * Network Interface
 * 
 * @class
 * @see {@link http://libvirt.org/html/libvirt-libvirt-interface.html#virInterface}
 */
var Interface = virt.Interface;

/**
 * Domain
 * 
 * @class
 * @see {@link http://libvirt.org/html/libvirt-libvirt-domain.html#virDomain}
 */
var Domain = virt.Domain;

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

/**
 * Registers a callback to be invoked when the connection event occurred
 * 
 * @param event {String}
 *        the name of event
 * @param listener {Function}
 *        the callback function
 */
Connection.prototype.addEventListener = function(event, listener) {
    return virt.addEventListener.apply(virt, arguments);
};

/**
 * Unregisters the callback previously set with the
 * {@link Connection#addEventListener()}
 * 
 * @param event {String}
 *        the name of event
 * @param listener {Function}
 *        the callback function
 */
Connection.prototype.removeEventListener = function(event, listener) {
    return virt.removeEventListener.apply(virt, arguments);
};

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
Connection.prototype.baselineCPU = function() {
    return virt.virConnectBaselineCPU.apply(virt, arguments);
};

/**
 * This function closes the connection to the Hypervisor.
 * 
 * @return {Number} a positive number if at least 1 reference remains on
 * success. The returned value should not be assumed to be the total
 * reference count. A return of 0 implies no references remain and the
 * connection is closed and memory has been freed.
 */
Connection.prototype.close = function() {
    return virt.virConnectClose.apply(virt, arguments);
};

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
Connection.prototype.compareCPU = function() {
    return virt.virConnectCompareCPU.apply(virt, arguments);
};

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
Connection.prototype.getCPUModelNames = function() {
    return virt.virConnectGetCPUModelNames.apply(virt, arguments);
};

/**
 * Get the capabilities of the hypervisor / driver.
 * 
 * @return {String} a XML string defining the capabilities.
 */
Connection.prototype.getCapabilities = function() {
    return virt.virConnectGetCapabilities.apply(virt, arguments);
};

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
Connection.prototype.getHostname = function() {
    return virt.virConnectGetHostname.apply(virt, arguments);
};

/**
 * Returns the version of libvirt used by the daemon running on the host
 * 
 * @param conn {Connection}
 *        hypervisor connection
 * @return {Number} libvirt library version used on the connection
 * @throws {Error}
 */
Connection.prototype.getLibVersion = function() {
    return virt.virConnectGetLibVersion.apply(virt, arguments);
};

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
Connection.prototype.getMaxVcpus = function() {
    return virt.virConnectGetMaxVcpus.apply(virt, arguments);
};

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
Connection.prototype.getSysinfo = function() {
    return virt.virConnectGetSysinfo.apply(virt, arguments);
};

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
Connection.prototype.getType = function() {
    return virt.virConnectGetType.apply(virt, arguments);
};

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
Connection.prototype.getURI = function() {
    return virt.virConnectGetURI.apply(virt, arguments);
};

/**
 * Get the version level of the Hypervisor running. This may work only with
 * hypervisor call, i.e. with privileged access to the hypervisor, not with
 * a Read-Only connection.
 * 
 * @return {Number} the version of the running hypervisor
 * @throws {Error}
 */
Connection.prototype.getVersion = function() {
    return virt.virConnectGetVersion.apply(virt, arguments);
};

/**
 * Determine if the connection to the hypervisor is still alive
 * 
 * @return {Boolean} true if alive, false if dead
 */
Connection.prototype.isAlive = function() {
    return virt.virConnectIsAlive.apply(virt, arguments);
};

/**
 * Determine if the connection to the hypervisor is encrypted
 * 
 * @return {Boolean} true if encrypted, false if not encrypted
 */
Connection.prototype.isEncrypted = function() {
    return virt.virConnectIsEncrypted.apply(virt, arguments);
};

/**
 * Determine if the connection to the hypervisor is secure
 * 
 * @return {Boolean} true if secure, false if not secure
 */
Connection.prototype.isSecure = function() {
    return virt.virConnectIsSecure.apply(virt, arguments);
};

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
Connection.prototype.ref = function() {
    return virt.virConnectRef.apply(virt, arguments);
};

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
Connection.prototype.setKeepAlive = function() {
    return virt.virConnectSetKeepAlive.apply(virt, arguments);
};

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
Connection.prototype.allocNodePages = function(allocations, startCell, cellCount, flags) {
    return virt.virNodeAllocPages.apply(virt, arguments);
};

/**
 * Get CPU map of host node CPUs
 * 
 * @return {Array} CPUs present on the host node
 * @throws {Error}
 */
Connection.prototype.getNodeCPUMap = function() {
    return virt.virNodeGetCPUMap.apply(virt, arguments);
};

/**
 * This function provides individual cpu statistics of the node. If you
 * want to get total cpu statistics of the node, you must specify
 * {@link VIR_NODE_CPU_STATS_ALL_CPUS} to <code>cpuNum</code>.
 * 
 * @param cpuNum {Number}
 *        number of node cpu
 * @return {Object}
 * @throws {Error}
 */
Connection.prototype.getNodeCPUStats = function() {
    return virt.virNodeGetCPUStats.apply(virt, arguments);
};

/**
 * Returns the free memory in one or more NUMA cells
 * 
 * @param startCell {Number}
 *        index of first cell
 * @return the free memory
 * @throws {Error}
 */
Connection.prototype.getNodeCellsFreeMemory = function(startCell) {
    return virt.virNodeGetCellsFreeMemory.apply(virt, arguments);
};

/**
 * Returns the free memory available on the Node
 * 
 * @return the available free memory in bytes
 * @throws {Error}
 */
Connection.prototype.getNodeFreeMemory = function() {
    return virt.virNodeGetFreeMemory.apply(virt, arguments);
};

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
Connection.prototype.getNodeFreePages = function(startCell, cellCount) {
    return virt.virNodeGetFreePages.apply(virt, arguments);
};

/**
 * Extract hardware information about the node.
 * 
 * @return {NodeInfo}
 * @throws {Error}
 */
Connection.prototype.getNodeInfo = function() {
    return virt.virNodeGetInfo.apply(virt, arguments);
};

/**
 * Get all node memory parameters (parameters unsupported by OS will be
 * omitted)
 * 
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.getNodeMemoryParameters = function() {
    return virt.virNodeGetMemoryParameters.apply(virt, arguments);
};

/**
 * Returns the memory stats of the node
 * 
 * @param cellNum {Number}
 *        number of node cell
 * @return {Object}
 * @throws {Error}
 */
Connection.prototype.getNodeMemoryStats = function() {
    return virt.virNodeGetMemoryStats.apply(virt, arguments);
};

/**
 * Returns the security model of a hypervisor
 * 
 * @return {Object}
 * @throws {Error}
 */
Connection.prototype.getNodeSecurityModel = function() {
    return virt.virNodeGetSecurityModel.apply(virt, arguments);
};

/**
 * Change all or a subset of the node memory tunables
 * 
 * @param params {Array}
 *        scheduler parameter objects
 * @throws {Error}
 */
Connection.prototype.setNodeMemoryParameters = function() {
    return virt.virNodeSetMemoryParameters.apply(virt, arguments);
};

/**
 * Attempt to suspend the node (host machine) for the given duration of time
 * in the specified state (Suspend-to-RAM, Suspend-to-Disk or Hybrid-Suspend).
 * Schedule the node's Real-Time-Clock interrupt to resume the node after the
 * duration is complete
 * 
 * @param target {Number}
 *        the state to which the host must be suspended to
 * @param duration {Number}
 *        the time duration in seconds for which the host has to be suspended
 * @throws {Error}
 */
Connection.prototype.suspendNodeForDuration = function() {
    return virt.virNodeSuspendForDuration.apply(virt, arguments);
};

/**
 * Returns the list of interfaces
 * 
 * @param flags
 *        bitwise-OR of virConnectListAllInterfacesFlags
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listAllInterfaces = function() {
    return virt.virConnectListAllInterfaces.apply(virt, arguments);
};

/**
 * Returns the list of defined (inactive) physical host interfaces
 * 
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listDefinedInterfaces = function() {
    return virt.virConnectListDefinedInterfaces.apply(virt, arguments);
};

/**
 * Returns the name of interfaces
 * 
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listInterfaces = function() {
    return virt.virConnectListInterfaces.apply(virt, arguments);
};

/**
 * Returns the number of defined (inactive) interfaces on the physical host
 * 
 * @return {Number}
 * @throws {Error}
 */
Connection.prototype.getNumberOfDefinedInterfaces = function() {
    return virt.virConnectNumOfDefinedInterfaces.apply(virt, arguments);
};

/**
 * Creates a restore point
 * 
 * @throws {Error}
 */
Connection.prototype.changeInterfaceBegin = function() {
    return virt.virInterfaceChangeBegin.apply(virt, arguments);
};

/**
 * Commits the changes made to interfaces
 * 
 * @throws {Error}
 */
Connection.prototype.changeInterfaceCommit = function() {
    return virt.virInterfaceChangeCommit.apply(virt, arguments);
};

/**
 * Cancels changes made to interfaces settings by restoring previous state
 * 
 * @throws {Error}
 */
Connection.prototype.changeInterfaceRollback = function() {
    return virt.virInterfaceChangeRollback.apply(virt, arguments);
};

/**
 * Define an inactive persistent physical host interface or modify an existing
 * persistent one from the XML description
 * 
 * @param xml {String}
 * @return {Interface}
 * @throws {Error}
 */
Connection.prototype.defineInterfaceXML = function() {
    return virt.virInterfaceDefineXML.apply(virt, arguments);
};

/**
 * Try to find a domain based on the hypervisor ID number Note that this won't
 * work for inactive domains which have an ID of -1, in that case a lookup
 * based on the Name or UUId need to be done instead.
 * 
 * @param id {Number}
 *        the domain ID number
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.lookupDomainById = function() {
    return virt.virDomainLookupByID.apply(virt, arguments);
};

/**
 * Try to lookup a domain on the given hypervisor based on its name.
 * 
 * @param name {String}
 *        the domain name
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.lookupDomainByName = function() {
    return virt.virDomainLookupByName.apply(virt, arguments);
};

/**
 * Try to lookup a domain on the given hypervisor based on its UUID.
 * 
 * @param uuid {String}
 *        the UUID string for the domain
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.lookupDomainByUUID = function() {
    return virt.virDomainLookupByUUIDString.apply(virt, arguments);
};

/**
 * Try to lookup an interface on the given hypervisor based on its name.
 * 
 * @param name {String}
 *        name for the interface
 * @return {Interface}
 * @throws {Error}
 */
Connection.prototype.lookupInterfaceByName = function() {
    return virt.virInterfaceLookupByName.apply(virt, arguments);
};

/**
 * Try to lookup an interface on the given hypervisor based on its MAC.
 * 
 * @param mac {String}
 *        the MAC for the interface (null-terminated ASCII format)
 * @return {Interface}
 * @throws {Error}
 */
Connection.prototype.lookupInterfaceByMACString = function() {
    return virt.virInterfaceLookupByMACString.apply(virt, arguments);
};

/**
 * Returns a possibly-filtered list of all domains
 * 
 * @param flags {Number}
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listAllDomains = function() {
    return virt.virConnectListAllDomains.apply(virt, arguments);
};

/**
 * Returns the defined but inactive domains
 *
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listDefinedDomains = function() {
    return virt.virConnectListDefinedDomains.apply(virt, arguments);
};

/**
 * Returns the list of active domains
 * 
 * @return {Array}
 * @throws {Error}
 */
Connection.prototype.listDomains = function() {
    return virt.virConnectListDomains.apply(virt, arguments);
};

/**
 * Returns he number of defined but inactive domains
 * 
 * @return {Number}
 * @throws {Error}
 */
Connection.prototype.getNumberOfDefinedDomains = function() {
    return virt.virConnectNumOfDefinedDomains.apply(virt, arguments);
};

/**
 * Returns the number of active domains
 * 
 * @return {Number}
 * @throws {Error}
 */
Connection.prototype.getNumberOfDomains = function() {
    return virt.virConnectNumOfDomains.apply(virt, arguments);
};

/**
 * Launch a new guest domain, based on an XML description
 * 
 * @param xml {String}
 *        string containing an XML description of the domain
 * @param flags {Number}
 *        bitwise-OR of supported virDomainCreateFlags
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.createDomainXML = function() {
    return virt.virDomainCreateXML.apply(virt, arguments);
};

/**
 * Launch a new guest domain, based on an XML description
 * 
 * @param xml {String}
 *        string containing an XML description of the domain
 * @param files {Array}
 *        list of file descriptors
 * @param flags {Number}
 *        bitwise-OR of supported virDomainCreateFlags
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.createDomainXMLWithFiles = function() {
    return virt.virDomainCreateXMLWithFiles.apply(virt, arguments);
};

/**
 * 
 * Define a domain, but does not start it. This definition is persistent,
 * until explicitly undefined with {@link Domain#undefine()}
 * 
 * @param xml {String}
 *        the XML description for the domain, preferably in UTF-8
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.defineDomainXML = function() {
    return virt.virDomainDefineXML.apply(virt, arguments);
};

/**
 * 
 * Define a domain, but does not start it. This definition is persistent,
 * until explicitly undefined with {@link Domain#undefine()}
 * 
 * @param xml {String}
 *        the XML description for the domain, preferably in UTF-8
 * @param flags {Number}
 *        bitwise OR of the virDomainDefineFlags constants
 * @return {Domain}
 * @throws {Error}
 */
Connection.prototype.defineDomainXMLFlags = function() {
    return virt.virDomainDefineXMLFlags.apply(virt, arguments);
};

/**
 * Adds a callback to receive notifications of domain lifecycle events
 * occurring on a connection. This function requires that an event loop has
 * been previously registered
 */
Domain.prototype.addEventListener = function(domainEventCallback, opaque) {
    return virt.virConnectDomainEventRegister.apply(virt, arguments);
};

/**
 * Removes a callback previously registered
 * 
 * @param domainEventCallback {Function}
 *        callback to the function handling domain events
 * @throws {Error}
 */
Domain.prototype.removeEventListener = function(domainEventCallback) {
    return virt.virConnectDomainEventDeregister.apply(virt, arguments);
};

/**
 * Removes an event callback
 * 
 * @param callbackId
 *        the callback identifier
 * @throws {Error}
 */
Domain.prototype.removeEventListenerAny = function(callbackId) {
    return virt.virConnectDomainEventDeregisterAny.apply(virt, arguments);
};

/**
 * Create a virtual device attachment to backend
 * 
 * @param xml {String}
 *        XML description of one device
 * @throws {Error}
 */
Domain.prototype.attachDevice = function() {
    return virt.virDomainAttachDevice.apply(virt, arguments);
};

/**
 * Commit changes that were made to temporary top-level files within a disk
 * image backing file chain into a lower-level base file
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param base {String}
 *        path to backing file to merge into, or device shorthand
 * @param top {String}
 *        path to file within backing chain that contains data to be merged,
 *        or device shorthand
 * @param bandWidth {Number}
 *        specify bandwidth limit
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockCommitFlags
 * @throws {Error}
 */
Domain.prototype.commitBlock = function() {
    return virt.virDomainBlockCommit.apply(virt, arguments);
};

/**
 * Copy the guest-visible contents of a disk image to a new file described by
 * the specified xml
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param xml {String}
 *        XML description of the copy destination
 * @param params {Object}
 *        block copy parameter objects
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockCopyFlags
 * @throws {Error}
 */
Domain.prototype.copyBlock = function() {
    return virt.virDomainBlockCopy.apply(virt, arguments);
};

/**
 * Cancel the active block job on the given disk.
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockJobAbortFlags
 * @throws {Error}
 */
Domain.prototype.abortBlockJob = function() {
    return virt.virDomainBlockJobAbort.apply(virt, arguments);
};

/**
 * Set the maximimum allowable bandwidth that a block job may consume
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param bandWidth {Number}
 *        specify bandwidth limit
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockJobSetSpeedFlags
 * @throws {Error}
 */
Domain.prototype.setBlockJobSpeed = function() {
    return virt.virDomainBlockJobSetSpeed.apply(virt, arguments);
};

/**
 * read the contents of a domain's disk device
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param offset {Number}
 *        offset within block device
 * @param size {Number}
 *        size to read
 * @return {ArrayBuffer}
 * @throws {Error}
 */
Domain.prototype.peekBlock = function() {
    return virt.virDomainBlockPeek.apply(virt, arguments);
};

/**
 * Populate a disk image with data from its backing image
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param bandWidth {Number}
 *        specify bandwidth limit
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockPullFlags
 * @throws {Error}
 */
Domain.prototype.pullBlock = function() {
    return virt.virDomainBlockPull.apply(virt, arguments);
};


/**
 * Populate a disk image with data from its backing image chain, and setting
 * the backing image to base
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param base {String}
 *        path to backing file to keep, or device shorthand, or null for no
 *        backing file
 * @param bandWidth {Number}
 *        specify bandwidth limit
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockRebaseFlags
 * @throws {Error}
 */
Domain.prototype.rebaseBlock = function() {
    return virt.virDomainBlockRebase.apply(virt, arguments);
};

/**
 * Resize a block device of domain while the domain is running
 * 
 * @param disk {String}
 *        path to the block image, or shorthand
 * @param size {Number}
 *        new size of the block image
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockResizeFlags
 * @throws {Error}
 */
Domain.prototype.resizeBlock = function() {
    return virt.virDomainBlockResize.apply(virt, arguments);
};

/**
 * Returns block device (disk) stats for block devices attached to the domain
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @return {Object}
 * @throws {Error}
 */
Domain.prototype.getBlockStats = function() {
    return virt.virDomainBlockStats.apply(virt, arguments);
};

/**
 * Returns block stats parameters for block devices attached to the domain
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param flags {Number}
 *        bitwise-OR of virTypedParameterFlags
 * @return {Array}
 */
Domain.prototype.getBlockStatsParameters = function() {
    return virt.virDomainBlockStatsFlags.apply(virt, arguments);
};

/**
 * Dump the core of a domain on a given file for analysis
 * 
 * @param to {String}
 *        path for the core file
 * @param flags {Number}
 *        bitwise-OR of virDomainCoreDumpFlags
 * @throws {Error}
 */
Domain.prototype.coreDump = function() {
    return virt.virDomainCoreDump.apply(virt, arguments);
};

/**
 * Dump the core of a domain on a given file for analysis
 * 
 * @param to {String}
 *        path for the core file
 * @param format {Number}
 *        format of domain memory's dump
 * @param flags {Number}
 *        bitwise-OR of virDomainCoreDumpFlags
 * @throws {Error}
 */
Domain.prototype.coreDumpWithFormat = function() {
    return virt.virDomainCoreDumpWithFormat.apply(virt, arguments);
};

/**
 * Launch a defined domain
 * 
 * @param flags {Number}
 *        bitwise-OR of supported virDomainCreateFlags
 * @throws {Error}
 */
Domain.prototype.create = function() {
    return virt.virDomainCreateWithFlags.apply(virt, arguments);
};

/**
 * Launch a defined domain
 * 
 * @param files {Array}
 *        list of file descriptors
 * @param flags {Number}
 *        bitwise-OR of supported virDomainCreateFlags
 * @throws {Error}
 */
Domain.prototype.createWithFiles = function() {
    return virt.virDomainCreateWithFiles.apply(virt, arguments);
};

/**
 * Destroy the domain object. The running instance is shutdown if not down
 * already and all resources used by it are given back to the hypervisor.
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainDestroyFlagsValues
 * @throws {Error}
 */
Domain.prototype.destroy = function() {
    return virt.virDomainDestroyFlags.apply(virt, arguments);
};

/**
 * Detach a virtual device from a domain, using the flags parameter to control
 * how the device is detached
 * 
 * @param xml {String}
 *        XML description of one device
 * @param flags {Number}
 *        bitwise-OR of virDomainDeviceModifyFlags
 * @throws {Error}
 */
Domain.prototype.detachDevice = function() {
    return virt.virDomainDetachDeviceFlags.apply(virt, arguments);
};

/**
 * Freeze specified filesystems within the guest
 * 
 * @param mnts {Array}
 *        list of mount points to be frozen
 * @return {Number} the number of frozen filesystems
 * @throws {Error}
 */
Domain.prototype.freezeFileSystem = function() {
    return virt.virDomainFSFreeze.apply(virt, arguments);
};

/**
 * Thaw specified filesystems within the guest
 * 
 * @param mnts {Array}
 *        list of mount points to be thaw
 * @return {Number} the number of thawed filesystems
 * @throws {Error}
 */
Domain.prototype.thawFileSystem = function() {
    return virt.virDomainFSThaw.apply(virt, arguments);
};

/**
 * Calls FITRIM within the guest
 * 
 * @param mnt {String}
 *        which mount point to trim
 * @param min {Number}
 *        Minimum contiguous free range to discard in bytes
 * @throws {Error}
 */
Domain.prototype.trimFileSystem = function() {
    return virt.virDomainFSTrim.apply(virt, arguments);
};

/**
 * Returns a boolean value indicating whether the domain configured to be
 * automatically started when the host machine boots
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Domain.prototype.getAutostart = function() {
    return virt.virDomainGetAutostart.apply(virt, arguments);
};

/**
 * Returns all blkio parameters
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} blkio parameter object
 * @throws {Error}
 */
Domain.prototype.getBlkioParameters = function() {
    return virt.virDomainGetBlkioParameters.apply(virt, arguments);
};

/**
 * Returns information about a domain's block device.
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @return {Object}
 * @throws {Error}
 */
Domain.prototype.getBlockInfo = function() {
    return virt.virDomainGetBlockInfo.apply(virt, arguments);
};

/**
 * Returns all block IO tunable parameters for a given device
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} blkio parameter objects
 * @throws {Error}
 */
Domain.prototype.getBlockIoTune = function() {
    return virt.virDomainGetBlockIoTune.apply(virt, arguments);
};

/**
 * Request block job information for the given disk
 * 
 * @param disk {String}
 *        path to the block device, or device shorthand
 * @param flags {Number}
 *        bitwise-OR of virDomainBlockJobInfoFlags
 * @return {Object} block job info
 * @throws {Error}
 */
Domain.prototype.getBlockJobInfo = function() {
    return virt.virDomainGetBlockJobInfo.apply(virt, arguments);
};

/**
 * Returns statistics relating to CPU usage attributable to a single domain
 * 
 * @param start {Number}
 *        which cpu to start with, or -1 for summary
 * @param ncpus {Number}
 *        how many cpus to query
 * @param flags {Number}
 *        bitwise-OR of virTypedParameterFlags
 * @return {Array} typed parameter objects
 * @throws {Error}
 */
Domain.prototype.getCPUStats = function() {
    return virt.virDomainGetCPUStats.apply(virt, arguments);
};

/**
 * Returns the connection pointer associated with a domain. The reference
 * counter on the connection is not increased by this call
 *
 * @return {Connection}
 * @throws {Error}
 */
Domain.prototype.getConnection = function() {
    return virt.virDomainGetConnect.apply(virt, arguments);
};

/**
 * Returns details about current state of control interface to a domain.
 * 
 * @return {Object} control info
 * @throws {Error}
 */
Domain.prototype.getControlInfo = function() {
    return virt.virDomainGetControlInfo.apply(virt, arguments);
};

/**
 * Returns all I/O errors that encountered with disks. Disks with no error will
 * not be returned
 */
Domain.prototype.getDiskErrors = function() {
    return virt.virDomainGetDiskErrors.apply(virt, arguments);
};

/**
 * Query the CPU affinity setting of all emulator threads of domain, store it
 * in cpumap.
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact Must not be
 *        VIR_DOMAIN_AFFECT_LIVE and VIR_DOMAIN_AFFECT_CONFIG concurrently.
 * @return {Array}
 * @throws {Error}
 */
Domain.prototype.getEmulatorPinInfo = function() {
    return virt.virDomainGetEmulatorPinInfo.apply(virt, arguments);
};

/**
 * Return a list of mapping information for each mounted file systems within
 * the specified guest and the disks
 * 
 * @return {Array} mount points information
 * @throws {Error}
 */
Domain.prototype.getFileSystemInfo = function() {
    return virt.virDomainGetFSInfo.apply(virt, arguments);
};

/**
 * Returns the hostname for that domain.
 * 
 * @return {String}
 * @throws {Error}
 */
Domain.prototype.getHostname = function() {
    return virt.virDomainGetHostname.apply(virt, arguments);
};

/**
 * Returns he hypervisor ID number for the domain
 */
Domain.prototype.getId = function() {
    return virt.virDomainGetID.apply(virt, arguments);
};

/**
 * Returns IOThreads of an active domain including the cpumap information to
 * determine on which CPU the IOThread has affinity to run
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact Must not be
 *        VIR_DOMAIN_AFFECT_LIVE and VIR_DOMAIN_AFFECT_CONFIG concurrently.
 * @return {Object} IOThread info
 * @throws {Error}
 */
Domain.prototype.getIOThreadInfo = function() {
    return virt.virDomainGetIOThreadInfo.apply(virt, arguments);
};

/**
 * Returns all interface parameters
 * 
 * @param device {String}
 *        the interface name or mac address
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} typed parameters
 * @throws {Error}
 */
Domain.prototype.getInterfaceParameters = function() {
    return virt.virDomainGetInterfaceParameters.apply(virt, arguments);
};

/**
 * Returns information about progress of a background job on a domain.
 * Will return an error if the domain is not active.
 * 
 * @return {Object} job information
 * @throws {Error}
 */
Domain.prototype.getJobInfo = function() {
    return virt.virDomainGetJobInfo.apply(virt, arguments);
};

/**
 * Returns information about progress of a background job on a domain
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainGetJobStatsFlags
 * @return {Array}
 */
Domain.prototype.getJobStats = function() {
    return virt.virDomainGetJobStats.apply(virt, arguments);
};

/**
 * Returns the maximum amount of physical memory allocated to a domain
 * 
 * @return {Number} the memory size in kibibytes (blocks of 1024 bytes)
 * @throws {Error}
 */
Domain.prototype.getMaxMemory = function() {
    return virt.virDomainGetMaxMemory.apply(virt, arguments);
};

/**
 * Returns the maximum number of virtual CPUs supported for the guest VM
 * 
 * @return {Number} the maximum of virtual CPU
 * @throws {Error}
 */
Domain.prototype.getMaxVcpus = function() {
    return virt.virDomainGetMaxVcpus.apply(virt, arguments);
};

/**
 * Returns all memory parameters
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} typed parameters
 * @throws {Error}
 */
Domain.prototype.getMemoryParameters = function() {
    return virt.virDomainGetMemoryParameters.apply(virt, arguments);
};

/**
 * Returns the appropriate domain element
 * 
 * @param type {Number}
 *        type of metadata, from virDomainMetadataType
 * @param uri {String}
 *        XML namespace identifier
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact
 * @return {String} the metadata string
 * @throws {Error}
 */
Domain.prototype.getMetadata = function() {
    return virt.virDomainGetMetadata.apply(virt, arguments);
};

/**
 * Returns the public name for that domain
 * 
 * @return {String} domain name
 */
Domain.prototype.getName = function() {
    return virt.virDomainGetName.apply(virt, arguments);
};

/**
 * Returns all numa parameters
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} typed parameters
 * @throws {Error}
 */
Domain.prototype.getNumaParameters = function() {
    return virt.virDomainGetNumaParameters.apply(virt, arguments);
};

/**
 * Returns the type of domain operation system.
 * 
 * @return {String}
 * @throws {Error}
 */
Domain.prototype.getOSType = function() {
    return virt.virDomainGetOSType.apply(virt, arguments);
};

/**
 * Returns all scheduler parameters
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact and virTypedParameterFlags
 * @return {Array} typed parameters
 * @throws {Error}
 */
Domain.prototype.getSchedulerParameters = function() {
    return virt.virDomainGetSchedulerParametersFlags.apply(virt, arguments);
};

/**
 * Returns the scheduler type
 * 
 * @return {String}
 * @throws {Error}
 */
Domain.prototype.getSchedulerType = function() {
    return virt.virDomainGetSchedulerType.apply(virt, arguments);
};

/**
 * Returns the security label of an active domain
 * 
 * @return {Object} security label
 * @throws {Error}
 */
Domain.prototype.getSecurityLabel = function() {
    return virt.virDomainGetSecurityLabel.apply(virt, arguments);
};

/**
 * Returns the security labels of an active domain
 */
Domain.prototype.getSecurityLabelList = function() {
    return virt.virDomainGetSecurityLabelList.apply(virt, arguments);
};

/**
 * Returns the domain state
 * 
 * @return {Object} domain state and reason
 * @throws {Error}
 */
Domain.prototype.getState = function() {
    return virt.virDomainGetState.apply(virt, arguments);
};

/**
 * Returns the guest time in nanoseconds
 * 
 * @return {Number}
 * @throws {Error}
 */
Domain.prototype.getTime = function() {
    return virt.virDomainGetTime.apply(virt, arguments);
};

/**
 * Returns the UUID for a domain
 * 
 * @return {String} UUID
 * @throws {Error}
 */
Domain.prototype.getUUID = function() {
    return virt.virDomainGetUUID.apply(virt, arguments);
};

/**
 * Returns the UUID for a domain as string
 * 
 * @return {String} UUID string
 * @throws {Error}
 */
Domain.prototype.getUUIDString = function() {
    return virt.virDomainGetUUIDString.apply(virt, arguments);
};

/**
 * Returns the CPU affinity setting of all virtual CPUs of domain
 * 
 * @param ncpumaps
 *        the number of cpumap
 * @param manlen
 *        the number of bytes in one cpumap
 * @param flags
 *        bitwise-OR of virDomainModificationImpact Must not be
 *        VIR_DOMAIN_AFFECT_LIVE and VIR_DOMAIN_AFFECT_CONFIG concurrently.
 * @return {Array} the virtual CPUs
 * @throws {Error}
 */
Domain.prototype.getVcpuPinInfo = function() {
    return virt.virDomainGetVcpuPinInfo.apply(virt, arguments);
};

/**
 * Returns the information about virtual CPUs of domain
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact Must not be
 *        VIR_DOMAIN_AFFECT_LIVE and VIR_DOMAIN_AFFECT_CONFIG concurrently.
 * @return {Array}
 * @throws {Error}
 */
Domain.prototype.getVcpus = function() {
    return virt.virDomainGetVcpus.apply(virt, arguments);
};

/**
 * Returns the number of virtual CPUs used by the domain
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainVcpuFlags
 * @return {Number}
 * @throws {Error}
 */
Domain.prototype.getVcpusFlags = function() {
    return virt.virDomainGetVcpusFlags.apply(virt, arguments);
};

/**
 * Returns the XML description of the domain
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainXMLFlags
 * @return {String}
 * @throws {Error}
 */
Domain.prototype.getXMLDesc = function() {
    return virt.virDomainGetXMLDesc.apply(virt, arguments);
};

/**
 * Check if a domain has a managed save image as created by
 * {@link Domain#managedSave()}.
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Domain.prototype.hasManagedSaveImage = function() {
    return virt.virDomainHasManagedSaveImage.apply(virt, arguments);
};

/**
 * Send NMI to the guest
 * 
 * @throws {Error}
 */
Domain.prototype.injectNMI = function() {
    return virt.virDomainInjectNMI.apply(virt, arguments);
};

/**
 * Returns the interfaces present in given domain along with their IP and MAC
 * addresses
 * 
 * @param source {Number}
 *        one of the virDomainInterfaceAddressesSource constants
 * @return {Array} interface objects
 * @throws {Error}
 */
Domain.prototype.getInterfaceAddresses = function() {
    return virt.virDomainInterfaceAddresses.apply(virt, arguments);
};

/**
 * Returns network interface stats for interfaces attached to the domain
 * 
 * @param path {String}
 *        path to the interface
 * @return {Array} interface stats
 * @throws {Error}
 */
Domain.prototype.getInterfaceStats = function() {
    return virt.virDomainInterfaceStats.apply(virt, arguments);
};

/**
 * Determine if the domain is currently running
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Domain.prototype.isActive = function() {
    return virt.virDomainIsActive.apply(virt, arguments);
};

/**
 * Determine if the domain has a persistent configuration which means it will
 * still exist after shutting down
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Domain.prototype.isPersistent = function() {
    return virt.virDomainIsPersistent.apply(virt, arguments);
};

/**
 * Determine if the domain has been updated
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Domain.prototype.isUpdated = function() {
    return virt.virDomainIsUpdated.apply(virt, arguments);
};

/**
 * Reboot a domain, the domain object is still usable thereafter, but the
 * domain OS is being stopped for a restart
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainRebootFlagValues
 * @throws {Error}
 */
Domain.prototype.reboot = function() {
    return virt.virDomainReboot.apply(virt, arguments);
};

/**
 * Increment the reference count on the domain
 * 
 * @throws {Error}
 */
Domain.prototype.ref = function() {
    return virt.virDomainRef.apply(virt, arguments);
};

/**
 * Reset a domain immediately without any guest OS shutdown. Reset emulates the
 * power reset button on a machine, where all hardware sees the RST line set
 * and reinitializes internal state.
 * 
 * @throws {Error}
 */
Domain.prototype.reset = function() {
    return virt.virDomainReset.apply(virt, arguments);
};

/**
 * Restore a domain saved to disk by {@link Domain#save()}
 * 
 * @param from {String}
 *        path to the input file
 * @param dxml {String}
 *        (optional) XML config for adjusting guest xml used on restore
 * @param flags {Number}
 *        bitwise-OR of virDomainSaveRestoreFlags
 * @throws {Error}
 */
Domain.prototype.restore = function() {
    return virt.virDomainRestoreFlags.apply(virt, arguments);
};

/**
 * Resume a suspended domain, the process is restarted from the state where it
 * was frozen by calling {@link Domain#suspend()}
 * 
 * @throws {Error}
 */
Domain.prototype.resume = function() {
    return virt.virDomainResume.apply(virt, arguments);
};

/**
 * Suspend a domain and save its memory contents to a file on disk
 * 
 * @param to {String}
 *        path for the output file
 * @param dxml {String}
 *        (optional) XML config for adjusting guest xml used on restore
 * @param flags {Number}
 *        bitwise-OR of virDomainSaveRestoreFlags
 * @throws {Error}
 */
Domain.prototype.save = function() {
    return virt.virDomainSaveFlags.apply(virt, arguments);
};

/**
 * Take a screenshot of current domain console as a stream
 * 
 * @param screen {Number}
 *        monitor ID to take screenshot from
 * @return {Object} the screenshot object
 * @throws {Error}
 */
Domain.prototype.screenshot = function() {
    return virt.virDomainScreenshot.apply(virt, arguments);
};

/**
 * Send key(s) to the guest.
 * 
 * @param codeset {Number}
 *        the code set of keycodes, from virKeycodeSet
 * @param holdtime {Number}
 *        the duration (in milliseconds) that the keys will be held
 * @param keycodes {Array}
 *        array of keycodes
 * @throws {Error}
 */
Domain.prototype.sendKey = function() {
    return virt.virDomainSendKey.apply(virt, arguments);
};

/**
 * Send a signal to the designated process in the guest
 * 
 * @param pid {Number}
 *        a positive integer process ID, or negative integer process group ID
 * @param signal {Number}
 *        a signal from the virDomainProcessSignal enum
 * @param flags {Number}
 *        one of the virDomainProcessSignalFlag values
 * @throws {Error}
 */
Domain.prototype.sendProcessSignal = function() {
    return virt.virDomainSendProcessSignal.apply(virt, arguments);
};

/**
 * Configure the domain to be automatically started when the host machine boots.
 * 
 * @param autostart {Boolean}
 *        whether the domain should be automatically started
 * @throws {Error}
 */
Domain.prototype.setAutostart = function() {
    return virt.virDomainSetAutostart.apply(virt, arguments);
};

/**
 * Sets the appropriate domain element given by type to the value of metadata
 * 
 * @param type {Number}
 *        type of metadata, from virDomainMetadataType
 * @param metadata {String}
          new metadata text
 * @param key {String}
          XML namespace key, or null
 * @param uri {String}
 *        XML namespace URI, or null
 * @param flags {Number}
 *        bitwise-OR of virDomainModificationImpact
 * @throws {Error}
 */
Domain.prototype.setMetadata = function() {
    return virt.virDomainSetMetadata.apply(virt, arguments);
};

/**
 * When a domain is suspended or restored from a file the domain's OS has no
 * idea that there was a big gap in the time. Depending on how long the gap
 * was, NTP might not be able to resynchronize the guest.
 * 
 * @param nanoseconds {Number}
 *        time to set, in nanoseconds
 * @param flags {Number}
 *        bitwise-OR of virDomainSetTimeFlags
 * @throws {Error}
 */
Domain.prototype.setTime = function() {
    return virt.virDomainSetTime.apply(virt, arguments);
};

/**
 * Shutdown a domain
 * 
 * @param flags {Number}
 *        bitwise-OR of virDomainShutdownFlagValues
 * @throws {Error}
 */
Domain.prototype.shutdown = function() {
    return virt.virDomainShutdownFlags.apply(virt, arguments);
};

/**
 * Suspends an active domain, the process is frozen without further access to
 * CPU resources and I/O but the memory used by the domain at the hypervisor
 * level will stay allocated
 * 
 * @throws {Error}
 */
Domain.prototype.suspend = function() {
    return virt.virDomainSuspend.apply(virt, arguments);
};

/**
 * Undefine a domain. If the domain is running, it's converted to transient
 * domain, without stopping it. If the domain is inactive, the domain
 * configuration is removed.
 * 
 * @param flags {Number}
 *        bitwise-OR of supported virDomainUndefineFlagsValues
 * @throws {Error}
 */
Domain.prototype.undefine = function() {
    return virt.virDomainUndefineFlags.apply(virt, arguments);
};

/**
 * @param xml {String}
 *        XML description of one device
 * @param flags {Number}
 *        bitwise-OR of virDomainDeviceModifyFlags
 * @throws {Error}
 */
Domain.prototype.updateDevice = function() {
    return virt.virDomainUpdateDeviceFlags.apply(virt, arguments);
};

/**
 * Activate an interface (i.e. call "ifup")
 * 
 * @throws {Error}
 */
Interface.prototype.create = function() {
    return virt.virInterfaceCreate.apply(virt, arguments);
};

/**
 * Deactivate an interface (ie call "ifdown")
 * 
 * @throws {Error}
 */
Interface.prototype.destroy = function() {
    return virt.virInterfaceDestroy.apply(virt, arguments);
};

/**
 * Returns the connection pointer associated with an interface
 * 
 * @return {Connection}
 * @throws {Error}
 */
Interface.prototype.getConnection = function() {
    return virt.virInterfaceGetConnect.apply(virt, arguments);
};

/**
 * Returns the MAC for an interface as string
 * 
 * @return {String}
 * @throws {Error}
 */
Interface.prototype.getMACString = function() {
    return virt.virInterfaceGetMACString.apply(virt, arguments);
};

/**
 * Returns the public name for that interface
 * 
 * @return {String}
 * @throws {Error}
 */
Interface.prototype.getName = function() {
    return virt.virInterfaceGetName.apply(virt, arguments);
};

/**
 * Returns the static configuration
 * 
 * @return {String}
 * @throws {Error}
 */
Interface.prototype.getXMLDesc = function() {
    return virt.virInterfaceGetXMLDesc.apply(virt, arguments);
};

/**
 * Determine if the interface is currently running
 * 
 * @return {Boolean}
 * @throws {Error}
 */
Interface.prototype.isActive = function() {
    return virt.virInterfaceIsActive.apply(virt, arguments);
};

/**
 * Increment the reference count on the interface
 * 
 * @throws {Error}
 */
Interface.prototype.ref = function() {
    return virt.virInterfaceRef.apply(virt, arguments);
};

/**
 * Undefine an interface, ie remove it from the config
 * 
 * @throws {Error}
 */
Interface.prototype.undefine = function() {
    return virt.virInterfaceUndefine.apply(virt, arguments);
};

(function(prototypes) {
    for (var i = 0; i < prototypes.length; i++) {
        var prototype = prototypes[i];

        for (var name in prototype) {
            var member = prototype[name];

            if ('function' !== typeof member)
                continue;

            (function(k, v) {
                this[k] = function() {
                    var args = Array.prototype.slice.apply(arguments);
                    args.unshift(this);
                    return v.apply(this, args);
                };
            }).call(prototype, name, member);
        }
    }
})([
    Connection.prototype,
    Domain.prototype,
    Interface.prototype,
]);

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

(function() {

    /**
     * Provides version information.
     * @return {Number} the library version
     * @throws {Error}
     */
    this.getVersion = function() {
        return virt.virGetVersion.apply(virt, arguments);
    };

    this.Connection = Connection;

    this.Interface = Interface;

}).call(module.exports);

