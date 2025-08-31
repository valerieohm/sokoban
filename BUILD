load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

# Export source files for use in other packages
exports_files([
    "src/board.cpp",
    "src/game.cpp",
    "include/board.hpp",
    "include/types.hpp",
    "include/game.hpp",
], visibility = ["//visibility:public"])

cc_library(
    name = "board_lib",
    srcs = ["src/board.cpp"],
    hdrs = ["include/board.hpp", "include/types.hpp"],
    includes = ["include"],
    visibility = ["//visibility:public"],
    copts = [
        "-g", 
        "-O0",
        "--coverage",  # Add coverage flags
    ],
    linkopts = [
        "--coverage",  # Link with coverage
    ],
)

cc_library(
    name = "game_lib",
    srcs = ["src/game.cpp"],
    hdrs = ["include/game.hpp"],
    deps = [":board_lib"],
    includes = ["include"],
    visibility = ["//visibility:public"],
    copts = [
        "-g", 
        "-O0",
        "--coverage",  # Add coverage flags
    ],
    linkopts = [
        "--coverage",  # Link with coverage
    ],
)

cc_binary(
    name = "hello_qt6",
    srcs = ["src/main.cpp"],
    deps = [":board_lib", ":game_lib"],
    copts = [
        "-I/usr/include/x86_64-linux-gnu/qt6",
        "-I/usr/include/x86_64-linux-gnu/qt6/QtCore",
        "-I/usr/include/x86_64-linux-gnu/qt6/QtGui",
        "-I/usr/include/x86_64-linux-gnu/qt6/QtWidgets",
        "-g", 
        "-O0",
    ],
    includes = [
        "include",
        "/usr/include/x86_64-linux-gnu/qt6",
        "/usr/include/x86_64-linux-gnu/qt6/QtCore",
        "/usr/include/x86_64-linux-gnu/qt6/QtGui",
        "/usr/include/x86_64-linux-gnu/qt6/QtWidgets",
    ],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lQt6Core",
        "-lQt6Gui",
        "-lQt6Widgets",
    ],
    visibility = ["//visibility:public"],
)
