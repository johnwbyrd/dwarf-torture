cmake_minimum_required(VERSION 3.18)
set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(hello-world LANGUAGES C CXX ASM)

add_executable(hello-world.prg hello-world.c)

# Use recommended optimization settings from AI.md
set_target_properties(hello-world.prg PROPERTIES
    CMAKE_BUILD_TYPE Debug
)
target_compile_options(hello-world.prg PRIVATE -O0 -flto -g)
target_link_options(hello-world.prg PRIVATE -flto)
