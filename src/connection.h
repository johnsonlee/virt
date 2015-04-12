#ifndef __CONNECTION_H__
#define __CONNECTION_H__

// libvirt
#include <libvirt/libvirt.h>

#include "pointer.h"

class Connection : public Pointer<virConnectPtr> {
private:

    static v8::Persistent<v8::Function> constructor;

    template <class F> friend class Pointer;
};

#endif /* __CONNECTION_H__ */
