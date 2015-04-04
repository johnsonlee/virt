#include <node.h>
#include <v8.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

#include <libvirt/libvirt.h>
#include <uuid/uuid.h>

struct virConnectAuthCallback
{
    v8::Handle<v8::Value> callback;
    v8::Handle<v8::Value> userdata;

    virConnectAuthCallback() : callback(NULL), userdata(NULL) {
    }
};

/**
 * All connections
 */
static std::map<const char*, virConnectPtr> connections;

/**
 * Lookup connection by URI
 */
static virConnectPtr lookup(v8::Handle<v8::Value> obj)
{
    typedef typename std::map<const char*, virConnectPtr>::const_iterator iterator_t;

    const v8::String::Utf8Value uri(obj->ToString());
    iterator_t i = connections.find(*uri);

    if (i != connections.end()) {
        return i->second;
    }

    return NULL;
}

/**
 * Provides version information
 */
static v8::Handle<v8::Value> __virGetVersion(const v8::Arguments& args)
{
    unsigned long libVer;
    v8::HandleScope scope;

    if (0 == virGetVersion(&libVer, NULL, NULL)) {
        return scope.Close(v8::Number::New(libVer));
    } else {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Unknown error")));
        return scope.Close(v8::Undefined());
    }
}

/**
 * Get node info
 * 
 * @param id {@Number}
 *           The connection id
 * @return the node detail information
 */
static v8::Handle<v8::Value> __virNodeGetInfo(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virNodeInfo info;
    virConnectPtr conn = lookup(args[0]);

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
static v8::Handle<v8::Value> __virNodeGetFreeMemory(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = lookup(args[0]);

    if (NULL != conn) {
        unsigned long long fm = virNodeGetFreeMemory(conn);

        return scope.Close(v8::Number::New(fm));
    }

    return scope.Close(v8::Undefined());
}

static v8::Handle<v8::Value> __virConnectBaselineCPU(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() < 4
            || !args[0]->IsString()
            || !args[1]->IsArray()
            || !args[2]->IsUint32()
            || !args[3]->IsUint32()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Invalid URI")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = lookup(args[0]);
    v8::Handle<v8::Array> cpus = v8::Handle<v8::Array>::Cast(args[1]);
    unsigned int ncpus = args[2]->Uint32Value();
    unsigned int flags = args[3]->Uint32Value();
    // char **xmlCPUs = NULL;
    // char *xml = virConnectBaselineCPU(conn, xmlCPUs, ncpus, flags);
    // TODO
    return scope.Close(v8::Undefined());
}

static v8::Handle<v8::Value> __virConnectOpen(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() < 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Invalid URI")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = NULL;
    v8::String::Utf8Value uri(args[0]->ToString());

    if (NULL != (conn = virConnectOpen(*uri))) {
        uuid_t raw = {0};
        char uuid[36] = {0};

        uuid_generate(raw);
        uuid_unparse(raw, uuid);
        connections[uuid] = conn;

        return scope.Close(v8::String::New(uuid));
    }

    return scope.Close(v8::Undefined());
}

#define __virConnectOpenReadOnly __virConnectOpen

static int __virConnectAuthCallback(virConnectCredentialPtr cred, unsigned int ncred, void *cbdata)
{
    virConnectAuthCallback *authData = reinterpret_cast<virConnectAuthCallback*>(cbdata);
    v8::Handle<v8::Value> callback = authData->callback;
    v8::Handle<v8::Value> userdata = authData->userdata;

    if (callback->IsFunction()) {
        v8::Local<v8::Object> global = v8::Context::GetCurrent()->Global();
        v8::Local<v8::Array> creds = v8::Array::New(ncred);
        v8::Handle<v8::Value> args[] = { creds, userdata };
        v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(callback);

        for (unsigned int i = 0; i < ncred; i++) {
            virConnectCredential *credPtr = cred + i;
            v8::Local<v8::Object> credential = v8::Object::New();

            credential->Set(v8::String::New("type"), v8::Integer::New(credPtr->type));
            credential->Set(v8::String::New("prompt"), v8::String::New(credPtr->prompt));
            credential->Set(v8::String::New("challenge"), v8::String::New(credPtr->challenge));
            credential->Set(v8::String::New("defresult"), v8::String::New(credPtr->defresult));
            credential->Set(v8::String::New("result"), v8::String::New(credPtr->result, credPtr->resultlen));

            creds->Set(i, credential);
        }

        func->Call(global, 2, args);
    }

    return 0;
}

/**
 * Open the specified URI with authentication
 * 
 * @param uri {@link String}
 *           The hypervisor URI
 * @param auth {@link Object}
 *           Authenticate parameters 
 * @param flags {@link Number}
 *           bitwise-OR of connect flags
 * @return connection id
 */
static v8::Handle<v8::Value> __virConnectOpenAuth(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() < 3
        || !args[0]->IsString()
        || !args[1]->IsObject()
        || !args[2]->IsUint32()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    v8::Handle<v8::Object> arg1 = v8::Handle<v8::Object>::Cast(args[1]);
    v8::Local<v8::Value> prop1 = arg1 ->Get(v8::String::New("credtypes"));
    v8::Local<v8::Value> prop2 = arg1->Get(v8::String::New("callback"));
    v8::Local<v8::Value> prop3 = arg1->Get(v8::String::New("userdata"));

    if (!prop1->IsArray()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    if (!prop2->IsFunction()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = NULL;
    virConnectAuth auth = {};
    virConnectAuthCallback cbAuth;
    v8::Handle<v8::Value> result = v8::Undefined();
    v8::String::Utf8Value uri(args[0]->ToString());
    v8::Local<v8::Array> credTypes = v8::Array::Cast(*prop1);
    uint32_t flags = args[2]->Uint32Value();

    if (credTypes->Length() > 0) {
        auth.ncredtype = credTypes->Length();
        auth.credtype = new int[auth.ncredtype];

        for (uint32_t i = 0; i < auth.ncredtype; i++) {
            v8::Local<v8::Value> credType = credTypes->Get(i);
            auth.credtype[i] = credType->IntegerValue();
        }
    }

    cbAuth.callback = prop2;
    cbAuth.userdata = prop3;
    auth.cbdata = &cbAuth;
    auth.cb = __virConnectAuthCallback;

    if (NULL != (conn = virConnectOpenAuth(*uri, &auth, flags))) {
        uuid_t raw = {0};
        char uuid[36] = {0};

        uuid_generate(raw);
        uuid_unparse(raw, uuid);
        connections[uuid] = conn;
        result = v8::String::New(uuid);
    }

    if (auth.credtype) {
        delete auth.credtype;
    }

    return scope.Close(result);
}

static v8::Handle<v8::Value> __virConnectClose(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() < 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    int result = 0;
    virConnectPtr conn = lookup(args[0]);

    if (NULL != conn && -1 != (result = virConnectClose(conn))) {
        v8::String::Utf8Value arg(args[0]->ToString());
        connections.erase(*arg);
        return scope.Close(v8::Integer::New(result));
    }

    return scope.Close(v8::Undefined());
}

static v8::Handle<v8::Value> __virConnectGetType(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() < 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = lookup(args[0]);
 
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
static v8::Handle<v8::Value> __virConnectGetVersion(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    unsigned long ver = 0UL;
    virConnectPtr conn = lookup(args[0]);
  
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
static v8::Handle<v8::Value> __virConnectGetHostname(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    virConnectPtr conn = lookup(args[0]);
  
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
static v8::Handle<v8::Value> __virConnectGetMaxVcpus(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if ((args.Length() < 1) || (!args[0]->IsString())
            || (args.Length() > 1 && !args[1]->IsString())) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    int vcpus = 0;
    virConnectPtr conn = lookup(args[0]);
  
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

static v8::Handle<v8::Value> __virConnectGetLibVersion(const v8::Arguments& args)
{
    v8::HandleScope scope;

    if (args.Length() != 1 || !args[0]->IsString()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Illegal arguments")));
        return scope.Close(v8::Undefined());
    }

    unsigned long ver = 0UL;
    virConnectPtr conn = lookup(args[0]);
  
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
    if (0 != virInitialize()) {
        v8::ThrowException(v8::Exception::Error(v8::String::New("Initialize virt error")));
        return;
    }

    /* ---------------------------- module host ---------------------------- */
    NODE_SET_METHOD(target, "virConnectBaselineCPU",   __virConnectBaselineCPU);
    NODE_SET_METHOD(target, "virConnectOpen",          __virConnectOpen);
    NODE_SET_METHOD(target, "virConnectOpenAuth",      __virConnectOpenAuth);
    NODE_SET_METHOD(target, "virConnectOpenReadOnly",  __virConnectOpenReadOnly);
    NODE_SET_METHOD(target, "virConnectClose",         __virConnectClose);
    NODE_SET_METHOD(target, "virConnectGetType",       __virConnectGetType);
    NODE_SET_METHOD(target, "virConnectGetVersion",    __virConnectGetVersion);
    NODE_SET_METHOD(target, "virConnectGetHostname",   __virConnectGetHostname);
    NODE_SET_METHOD(target, "virConnectGetMaxVcpus",   __virConnectGetMaxVcpus);
    NODE_SET_METHOD(target, "virConnectGetLibVersion", __virConnectGetLibVersion);
    NODE_SET_METHOD(target, "virGetVersion",           __virGetVersion);
    NODE_SET_METHOD(target, "virNodeGetInfo",          __virNodeGetInfo);
    NODE_SET_METHOD(target, "virNodeGetFreeMemory",    __virNodeGetFreeMemory);
}

#ifdef __cplusplus
}
#endif

NODE_MODULE(virt, init)
