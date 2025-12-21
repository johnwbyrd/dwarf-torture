cmake_minimum_required(VERSION 3.18)

# MOS toolchain setup - must be before project()
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR mos)

# Toolchain paths
set(LLVM_MOS "$ENV{HOME}/git/llvm-mos/build/install")
set(PICOLIBC "$ENV{HOME}/git/picolibc/build-mos/install/usr/local/picolibc/mos")

# Use full triple variant so --print-libgcc-file-name returns correct path
set(CMAKE_C_COMPILER "${LLVM_MOS}/bin/mos-unknown-unknown-clang")
set(CMAKE_CXX_COMPILER "${LLVM_MOS}/bin/mos-unknown-unknown-clang++")
set(CMAKE_ASM_COMPILER "${LLVM_MOS}/bin/mos-unknown-unknown-clang")
set(CMAKE_AR "${LLVM_MOS}/bin/llvm-ar")
set(CMAKE_RANLIB "${LLVM_MOS}/bin/llvm-ranlib")

# Prevent CMake from testing the compiler (cross-compiling)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(dwarf-torture LANGUAGES C ASM)

# picolibc paths
set(PICOLIBC_INCLUDE "${PICOLIBC}/include")
set(PICOLIBC_LIB "${PICOLIBC}/lib")

# Common compile flags (need endianness defines for picolibc)
set(COMMON_FLAGS "-nostdlib -isystem ${PICOLIBC_INCLUDE} -g -D__IEEE_LITTLE_ENDIAN -D_LDBL_EQ_DBL")

# Common link flags for ZBC semihosting
set(COMMON_LINK_FLAGS
    "-nostdlib"
    "-L${PICOLIBC_LIB}"
    "-T${PICOLIBC_LIB}/picolibc.ld"
    "${PICOLIBC_LIB}/crt0-semihost-zbc.o"
    "-lc"
    "-lm"
    "-lsemihost"
)

# Get the clang runtime library path
execute_process(
    COMMAND ${CMAKE_C_COMPILER} --print-libgcc-file-name
    OUTPUT_VARIABLE CLANG_RT_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
get_filename_component(CLANG_RT_DIR "${CLANG_RT_PATH}" DIRECTORY)
list(APPEND COMMON_LINK_FLAGS "-L${CLANG_RT_DIR}" "-lclang_rt.builtins")

# Convert link flags list to string for CMake
string(REPLACE ";" " " LINK_FLAGS_STR "${COMMON_LINK_FLAGS}")

set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINK_FLAGS_STR}")

# Helper function to add a test executable
function(add_dwarf_test name)
    add_executable(${name} ${ARGN})
    # Output is ELF (no extension), suitable for mame -elfload
    set_target_properties(${name} PROPERTIES
        SUFFIX ""
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endfunction()

# Add test subdirectory
add_subdirectory(tests)
