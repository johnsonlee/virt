#ifndef __CONNECTION_H__
#define __CONNECTION_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virConnectPtr>;

class Connection : public Pointer<virConnectPtr> {
private:
    static v8::Persistent<v8::Function> constructor;

    inline Connection(virConnectPtr ptr) : Pointer(ptr) {}

    friend class Pointer<virConnectPtr>;
};

#endif /* __CONNECTION_H__ */
