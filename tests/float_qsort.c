// Simple quicksort for floats - test DWARF debug info at various optimization levels

#include <stdio.h>

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int partition(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Simple main to exercise the sort
float test_array[5] = {3.14f, 1.41f, 2.72f, 0.58f, 1.73f};

int main(void) {
    int n = 5;
    printf("Sorting %d floats\n", n);
    quicksort(test_array, 0, n - 1);
    printf("Done\n");
    return 0;
}
