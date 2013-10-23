## virt

This package is a wrapper of libvirt for node js.

The wrappered API is almost the same as libvirt, about libvirt, please see:
  API Reference: http://libvirt.org/html/libvirt-libvirt.html
  Development Guide: http://libvirt.org/devguide.html


## example

``` js

var virt = require('virt');

var conn = virt.virConnectOpen('qemu:///system');

if (conn) {
    var info = virt.virNodeGetInfo(conn);
    var free = virt.virNodeGetFreeMemory(conn);
    var version = virt.virConnectGetVersion(conn);
    var libVersion = virt.virConnectGetLibVersion(conn);

    console.log('Info: ' + JSON.stringify(info));
    console.log('Free Memory: ' + free);

    console.log('Version: ' + version);
    console.log('Lib Version: ' + libVersion);

    virt.virConnectClose();
}
```


## TODO

 - Add non-*nix platform support


## License

Copyright (c) 2013, Johnson Lee (MIT License).

