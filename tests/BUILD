load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_test(
    name = "board_test",
    srcs = ["board_test.cpp"],
    copts = [
        "-g",
        "-O0",
    ],
    deps = [
        "//:board_lib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "types_test",
    srcs = ["types_test.cpp"],
    copts = [
        "-g",
        "-O0",
    ],
    deps = [
        "//:board_lib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "game_test",
    srcs = ["game_test.cpp"],
    copts = [
        "-g",
        "-O0",
    ],
    deps = [
        "//:board_lib",
        "//:game_lib",
        "@googletest//:gtest_main",
    ],
)
