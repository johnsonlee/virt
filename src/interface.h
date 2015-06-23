#ifndef __INTERFACE_H__
#define __INTERFACE_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

template class Pointer<virInterfacePtr>;

class Interface : public Pointer<virInterfacePtr> {
private:
    static v8::Persistent<v8::Function> constructor;

    inline Interface(virInterfacePtr ptr) : Pointer(ptr) {}

    friend class Pointer<virInterfacePtr>;
};

#endif /* __INTERFACE_H__ */
