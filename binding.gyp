{
    "targets" : [
        {
            "target_name" : "virt",
            "sources" : [
                "src/virt.cc",
                "src/connection.cc",
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
