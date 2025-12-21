// Test DWARF with nested structs, unions, and complex types
#include <stdio.h>
#include <stdint.h>

struct Point {
    int16_t x;
    int16_t y;
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Rectangle {
    struct Point origin;
    struct Point size;
    struct Color fill;
    struct Color stroke;
};

union ValueUnion {
    int16_t as_int;
    uint16_t as_uint;
    uint8_t as_bytes[2];
    struct {
        uint8_t low;
        uint8_t high;
    } parts;
};

struct ComplexObject {
    char name[8];
    struct Rectangle bounds;
    union ValueUnion value;
    uint8_t flags;
    struct Point *next_point;  // pointer to struct
};

__attribute__((noinline))
int process_rectangle(struct Rectangle *rect) {
    // Access nested struct members
    int area = rect->size.x * rect->size.y;
    int brightness = rect->fill.r + rect->fill.g + rect->fill.b;

    // Breakpoint here - inspect rect and its nested members
    printf("Area: %d, Brightness: %d\n", area, brightness);

    return area + brightness;
}

__attribute__((noinline))
int process_complex(struct ComplexObject *obj) {
    // Access deeply nested members
    int x = obj->bounds.origin.x;
    int y = obj->bounds.origin.y;

    // Access union members
    int val = obj->value.as_int;
    uint8_t low = obj->value.parts.low;
    uint8_t high = obj->value.parts.high;

    // Breakpoint here - inspect complex object
    printf("Pos: (%d,%d) Val: %d (0x%02x, 0x%02x)\n", x, y, val, low, high);

    return process_rectangle(&obj->bounds);
}

// Global instances for testing
struct Point global_point = {100, 200};

struct ComplexObject global_object = {
    .name = "Test",
    .bounds = {
        .origin = {10, 20},
        .size = {30, 40},
        .fill = {255, 128, 64, 255},
        .stroke = {0, 0, 0, 255}
    },
    .value = {.as_int = 0x1234},
    .flags = 0x42,
    .next_point = &global_point
};

int main(void) {
    // Local struct on stack
    struct Rectangle local_rect = {
        .origin = {5, 10},
        .size = {15, 25},
        .fill = {200, 100, 50, 255},
        .stroke = {10, 20, 30, 128}
    };

    int r1 = process_rectangle(&local_rect);
    int r2 = process_complex(&global_object);

    printf("Results: %d, %d\n", r1, r2);
    return 0;
}
