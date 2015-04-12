{
    "targets" : [
        {
            "target_name" : "virt",
            "sources" : [
                "src/connection.cc",
                "src/domain.cc",
                "src/interface.cc",
                "src/virt.cc",
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
