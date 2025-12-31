# DWARF torture tests
# Each test can be built at multiple optimization levels

# float_qsort - tests float variables and function calls
add_dwarf_test(float_qsort_O0 float_qsort.c)
target_compile_options(float_qsort_O0 PRIVATE -O0)

add_dwarf_test(float_qsort_O1 float_qsort.c)
target_compile_options(float_qsort_O1 PRIVATE -O1)

add_dwarf_test(float_qsort_O2 float_qsort.c)
target_compile_options(float_qsort_O2 PRIVATE -O2)

add_dwarf_test(float_qsort_Os float_qsort.c)
target_compile_options(float_qsort_Os PRIVATE -Os)

add_dwarf_test(float_qsort_Oz float_qsort.c)
target_compile_options(float_qsort_Oz PRIVATE -Oz)

# hello_world - simple sanity check
add_dwarf_test(hello_world hello_world.c)
target_compile_options(hello_world PRIVATE -O0)

# many_locals - stress soft stack with 20+ local variables
add_dwarf_test(many_locals_O0 many_locals.c)
target_compile_options(many_locals_O0 PRIVATE -O0)

# nested_structs - complex types: nested structs, unions, pointers
add_dwarf_test(nested_structs_O0 nested_structs.c)
target_compile_options(nested_structs_O0 PRIVATE -O0)

# deep_recursion - stress unwinder with 15+ frame depth
add_dwarf_test(deep_recursion_O0 deep_recursion.c)
target_compile_options(deep_recursion_O0 PRIVATE -O0)
