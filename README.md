# dwarf-torture

Test suite for DWARF debug information on the MOS 6502 architecture. These tests validate that source-level debugging works correctly with LLVM-MOS and LLDB.

## Overview

The MOS 6502 has a unique dual-stack architecture:
- **Hardware stack** (S register, 0x0100-0x01FF): return addresses and callee-saved registers
- **Soft stack** (RS0 pointer): local variables and spilled values

This creates challenges for DWARF CFI (Call Frame Information) that these tests are designed to stress.

## Prerequisites

- LLVM-MOS built and installed at `~/git/llvm-mos/build/install`
- picolibc for MOS at `~/git/picolibc/build-mos/install`
- MAME with the `zbcm6502` machine (for running tests)

## Building

```bash
mkdir -p build && cd build
cmake ..
make
```

Or use the integrated build script in llvm-mos:

```bash
~/git/llvm-mos/.vscode/build-all.sh
```

This builds llvm-mos, picolibc, and dwarf-torture together.

## Test Programs

### hello_world.c
Simple sanity check. Verifies the build system works.

### float_qsort.c
Quicksort implementation with floating-point values. Tests:
- Function calls and recursion
- Local variable inspection across optimization levels
- Built at -O0, -O1, and -O2

### many_locals.c
Function with 20+ local variables of various types (int8_t, int16_t, uint8_t, uint16_t, int). Tests:
- Soft stack frame with many variables
- Variable inspection at nested call depths
- Type correctness for different integer sizes

### nested_structs.c
Complex type hierarchies including:
- Nested structs (Point inside Rectangle)
- Unions with multiple interpretations
- Pointers to structs
- Both global and local struct instances

### deep_recursion.c
Recursive functions reaching 15+ stack frames. Tests:
- Stack unwinding through many frames
- Distinct local variables at each recursion level
- Mixed recursion patterns (alternating functions)

## Output Binaries

Test binaries are ELF files in `build/bin/`, suitable for:
- `mame zbcm6502 -elfload <binary>` (direct execution)
- `mame zbcm6502 -debugger gdbstub -debug -elfload <binary>` (debugging)
