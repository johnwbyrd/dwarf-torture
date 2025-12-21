// Test DWARF with many local variables - stress the soft stack
#include <stdio.h>
#include <stdint.h>

// Force no inlining so we get a real stack frame
__attribute__((noinline))
int compute_with_many_locals(int seed) {
    // 20+ locals of various types
    int8_t a = seed;
    int8_t b = seed + 1;
    int8_t c = seed + 2;
    int8_t d = seed + 3;

    int16_t e = seed * 2;
    int16_t f = seed * 3;
    int16_t g = seed * 4;
    int16_t h = seed * 5;

    uint8_t i = seed & 0xFF;
    uint8_t j = (seed >> 1) & 0xFF;
    uint8_t k = (seed >> 2) & 0xFF;
    uint8_t l = (seed >> 3) & 0xFF;

    uint16_t m = seed | 0x100;
    uint16_t n = seed | 0x200;
    uint16_t o = seed | 0x300;
    uint16_t p = seed | 0x400;

    int q = a + b + c + d;
    int r = e + f + g + h;
    int s = i + j + k + l;
    int t = m + n + o + p;

    // Use all variables to prevent optimization
    int result = q + r + s + t;

    // Breakpoint here - all locals should be visible
    printf("Result: %d\n", result);

    return result;
}

__attribute__((noinline))
int outer_function(int x) {
    int local1 = x * 2;
    int local2 = x * 3;
    // Call inner function - creates nested frames
    int inner_result = compute_with_many_locals(local1 + local2);
    return inner_result + local1 + local2;
}

int main(void) {
    int input = 7;
    int output = outer_function(input);
    printf("Final: %d\n", output);
    return 0;
}
