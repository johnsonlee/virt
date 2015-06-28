{
    "targets" : [
        {
            "target_name" : "virt",
            "sources" : [
                "src/virt-domain.h",
                "src/virt-domain.cc",
                "src/virt-domain-snapshot.h",
                "src/virt-domain-snapshot.cc",
                "src/virt-event.h",
                "src/virt-event.cc",
                "src/virt-host.h",
                "src/virt-host.cc",
                "src/virt-interface.h",
                "src/virt-interface.cc",
                "src/virt-network.h",
                "src/virt-network.cc",
                "src/virt-node-device.h",
                "src/virt-node-device.cc",
                "src/virt-network-filter.h",
                "src/virt-network-filter.cc",
                "src/virt-secret.h",
                "src/virt-secret.cc",
                "src/virt-storage.h",
                "src/virt-storage.cc",
                "src/virt-stream.h",
                "src/virt-stream.cc",
                "src/virt.cc"
            ],
            "include_dirs" : [
                "/usr/local/include",
            ],
            "libraries" : [
                "-lvirt",
                "-L/usr/local/lib",
            ]
        }
    ]
}
