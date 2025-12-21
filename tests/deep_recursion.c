// Test DWARF with deep recursion - stress the unwinder
#include <stdio.h>
#include <stdint.h>

#define MAX_DEPTH 15

// Each frame has distinct locals to verify correct unwinding
__attribute__((noinline))
int recursive_sum(int depth, int accumulator) {
    // Local variables unique to each frame
    int local_depth = depth;
    int local_acc = accumulator;
    int frame_contribution = depth * 2;

    if (depth <= 0) {
        // Breakpoint here at max depth - check full backtrace
        printf("Base case: acc=%d\n", local_acc);
        return local_acc;
    }

    // Recurse
    int result = recursive_sum(depth - 1, local_acc + frame_contribution);

    // Use locals after recursion returns
    return result + local_depth;
}

// Alternating function to create mixed call patterns
__attribute__((noinline))
int helper_function(int n, int acc) {
    int helper_local = n + 100;

    if (n <= 0) {
        return acc;
    }

    // Alternate between helper and recursive
    if (n % 2 == 0) {
        return recursive_sum(n - 1, acc + helper_local);
    } else {
        return helper_function(n - 1, acc + helper_local);
    }
}

int main(void) {
    int start_value = 5;

    printf("Starting recursion test with depth %d\n", MAX_DEPTH);

    int result1 = recursive_sum(MAX_DEPTH, start_value);
    printf("Pure recursion result: %d\n", result1);

    int result2 = helper_function(10, 0);
    printf("Mixed recursion result: %d\n", result2);

    return 0;
}
