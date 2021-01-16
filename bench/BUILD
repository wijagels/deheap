load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "functions_bench",
    srcs = [
        "deheap_bench.cpp",
    ],
    deps = [
        "//:deheap",
        "@com_github_google_benchmark//:benchmark_main",
    ],
)
