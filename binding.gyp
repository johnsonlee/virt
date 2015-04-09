{
    "targets" : [
        {
            "target_name" : "virt",
            "sources" : [
                "src/native-class.cc",
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
