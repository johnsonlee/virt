# virt

This package is a wrapper of libvirt for node js.

## Overview

The wrappered API is almost the same as libvirt, about libvirt, please see:

 * API Reference: http://libvirt.org/html/libvirt-libvirt.html
 * Development Guide: http://libvirt.org/devguide.html

## Dependencies

- libvirt
- node.js v0.10.x or higher

## References

Please see [API doc](https://rawgit.com/johnsonlee/virt/master/doc/index.html)

## Example

``` js
var Connection = require('virt').Connection;

var conn = Connection.open('vbox:///session');

try {
    var capabilities = conn.getCapabilities();
    console.log(capabilities);

    var hostname = conn.getHostname();
    console.log(hostname);

    ver libVersion = conn.getLibVersion();
    console.log(libVersion);

    var nodeInfo = conn.getNodeInfo();
    console.log(JSON.stringify(nodeInfo));
} catch (e) {
    console.log(e.stack);
} finally {
    if (conn) {
        conn.close();
    }
}
```

## TODO

 - Add non-*nix platform support

## License

Copyright (c) 2013-2015, Johnson Lee (MIT License).

