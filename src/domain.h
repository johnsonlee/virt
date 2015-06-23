#ifndef __DOMAIN_H__
#define __DOMAIN_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virDomainPtr>;

class Domain : public Pointer<virDomainPtr> {
private:
    static v8::Persistent<v8::Function> constructor;

    inline Domain(virDomainPtr ptr) : Pointer(ptr) {}

    friend class Pointer<virDomainPtr>;
};

#endif /* __DOMAIN_H__ */
