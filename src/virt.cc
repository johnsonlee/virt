#include <node.h>
#include <v8.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

#include <libvirt/libvirt.h>
#include <uuid/uuid.h>

/**
 * All connections
 */
static std::map<std::string, virConnectPtr> connections;

static virConnectPtr getConnection(v8::Handle<v8::Value> obj)
{
    typedef typename std::map<std::string, virConnectPtr>::iterator iterator;

    v8::String::Utf8Value arg(obj->ToString());
    char *key = strdup(*arg);
    iterator it = connections.find(key);

    free(key);

    if (it != connections.end()) {
        return it->second;
    }

    return NULL;
}

/**
 * Get node info
 * 
 * @param id {@Number}
 *           The connection id
 * @return the node detail information
 */
static v8::Handle<v8::Value> VirtualNode_info(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virNodeInfo info;
    virConnectPtr conn = getConnection(args[0]);

    if (NULL != conn && 0 == virNodeGetInfo(conn, &info)) {
        v8::Local<v8::Object> obj = v8::Object::New();

        obj->Set(v8::String::New("model"), v8::String::New(info.model));
        obj->Set(v8::String::New("memory"), v8::Number::New(info.memory));
        obj->Set(v8::String::New("cpus"), v8::Number::New(info.cpus));
        obj->Set(v8::String::New("mhz"), v8::Number::New(info.mhz));
        obj->Set(v8::String::New("nodes"), v8::Number::New(info.nodes));
        obj->Set(v8::String::New("sockets"), v8::Number::New(info.sockets));
        obj->Set(v8::String::New("cores"), v8::Number::New(info.cores));
        obj->Set(v8::String::New("threads"), v8::Number::New(info.threads));

        return scope.Close(obj);
    }

    return scope.Close(v8::Undefined());
}

/**
 * Get node free memory
 */
static v8::Handle<v8::Value> VirtualNode_freeMemory(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = getConnection(args[0]);

    if (NULL != conn) {
        unsigned long long fm = virNodeGetFreeMemory(conn);

        return scope.Close(v8::Number::New(fm));
    }

    return scope.Close(v8::Undefined());
}

/**
 * Open the specified QEMU URI
 * 
 * @param uri {@link String}
 *           QEMU URI
 * @return connection id
 */
static v8::Handle<v8::Value> VirtualConnection_open(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("libvirt URI format error")));
        return scope.Close(v8::Undefined());
    }

    uuid_t raw = {0};
    char uuid[36] = {0};
    virConnectPtr conn = NULL;
    v8::String::Utf8Value uri(args[0]->ToString());

    conn = virConnectOpen(*uri);
    uuid_generate(raw);
    uuid_unparse_lower(raw, uuid);
    connections[uuid] = conn;

    return scope.Close(v8::String::New(uuid));
}

/**
 * Close the connection by id
 * 
 * @param id {@link Number}
 *           The connection id
 */
static v8::Handle<v8::Value> VirtualConnection_close(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = getConnection(args[0]);

    if (NULL != conn && 0 == virConnectClose(conn)) {
        v8::String::Utf8Value arg(args[0]->ToString());

        connections.erase(*arg);
    }

    return scope.Close(v8::Undefined());
}

/**
 * Get connection type
 * 
 * @param id {@link Number}
 *           The connectionn id
 * 
 * @return the type string
 */
static v8::Handle<v8::Value> VirtualConnection_type(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = getConnection(args[0]);
 
    if (NULL != conn) {
        const char *type = virConnectGetType(conn);
        return scope.Close(v8::String::New(type));
    }

    return scope.Close(v8::Undefined());
}

/**
 * Get connection version
 * 
 * @param id {@link Number}
 *           The connectionn id
 * 
 * @return the version number
 */
static v8::Handle<v8::Value> VirtualConnection_version(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    unsigned long ver = 0UL;
    virConnectPtr conn = getConnection(args[0]);
  
    if (NULL != conn && 0 == virConnectGetVersion(conn, &ver)) {
        return scope.Close(v8::Number::New(ver));
    }

    return scope.Close(v8::Undefined());
}

/**
 * Get connection hostname
 * 
 * @param id {@link Number}
 *           The connectionn id
 * 
 * @return the hostname
 */
static v8::Handle<v8::Value> VirtualConnection_hostname(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = getConnection(args[0]);
  
    if (NULL != conn) {
        char *host = virConnectGetHostname(conn);
        return scope.Close(v8::String::New(host));
    }

    return scope.Close(v8::Undefined());
}

/**
 * Get the max virtual cpu number of connection
 * 
 * @param id {@link Number}
 *           The connectionn id
 * @param type {@link String}
 *           The virtulization type (optional)
 * 
 * @return the max virtual cpu number
 */
static v8::Handle<v8::Value> VirtualConnection_maxVcpus(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if ((args.Length() < 1) || (!args[0]->IsString())
            || (args.Length() > 1 && !args[1]->IsString())) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    int vcpus = 0;
    virConnectPtr conn = getConnection(args[0]);
  
    if (NULL != conn) {
        if (args.Length() > 1) {
            v8::String::Utf8Value type(args[1]->ToString());
            vcpus = virConnectGetMaxVcpus(conn, *type);
        } else {
            vcpus = virConnectGetMaxVcpus(conn, NULL);
        }
        
    }

    return scope.Close(v8::Integer::New(vcpus));
}

/**
 * Get connection lib version
 * 
 * @param id {@link Number}
 *           The connectionn id
 * 
 * @return the version number
 */
static v8::Handle<v8::Value> VirtualConnection_libVersion(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    unsigned long ver = 0UL;
    virConnectPtr conn = getConnection(args[0]);
  
    if (NULL != conn && 0 == virConnectGetLibVersion(conn, &ver)) {
        return scope.Close(v8::Number::New(ver));
    }

    return scope.Close(v8::Undefined());
}

#ifdef __cplusplus
extern "C" {
#endif

void init(v8::Handle<v8::Object> target)
{
    v8::HandleScope scope;

    NODE_SET_METHOD(target, "virNodeGetInfo",          VirtualNode_info);
    NODE_SET_METHOD(target, "virNodeGetFreeMemory",    VirtualNode_freeMemory);

    NODE_SET_METHOD(target, "virConnectOpen",          VirtualConnection_open);
    NODE_SET_METHOD(target, "virConnectClose",         VirtualConnection_close);
    NODE_SET_METHOD(target, "virConnectGetType",       VirtualConnection_type);
    NODE_SET_METHOD(target, "virConnectGetVersion",    VirtualConnection_version);
    NODE_SET_METHOD(target, "virConnectGetHostname",   VirtualConnection_hostname);
    NODE_SET_METHOD(target, "virConnectGetMaxVcpus",   VirtualConnection_maxVcpus);
    NODE_SET_METHOD(target, "virConnectGetLibVersion", VirtualConnection_libVersion);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, init)
