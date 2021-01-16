load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "deheap",
    hdrs = [
        "include/deheap/deheap.hpp",
        "include/deheap/deheap.ipp",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = [":functions"],
)

cc_library(
    name = "functions",
    hdrs = [
        "include/deheap/functions.hpp",
        "include/deheap/functions.ipp",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
)
