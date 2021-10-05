#include <stdio.h>
#include <inttypes.h>

void insertion_sort (int32_t values[], int32_t num_vals);
void print_array(int32_t values[], int32_t num_vals);

int main()
{
    int32_t array[10] = { 10, 3, -6, -8, 9, -11, 12, -16, -44, 1 };
    int32_t num_vals = 10;

    printf("Unsorted array:\n");
    print_array(array, num_vals);

    insertion_sort(array, num_vals);

    printf("\nSorted array:\n");
    print_array(array, num_vals);

    return 0;
}


void print_array(int32_t values[], int32_t num_vals)
{
    int32_t index;

    for (index = 0; index < num_vals; index++) {
        printf ("%i ", values[index]);
    }

    printf("\n");
}

void insertion_sort (int32_t values[], int32_t num_vals)
{
    int32_t sorted, current, index;
    for (sorted = 2; num_vals >= sorted; sorted++) {
        current = values[sorted - 1];
        for (index = sorted - 1; 0 < index; index--) {
            if (current >= values[index - 1]) {
                break;
            }
            values[index] = values[index - 1];
        }
        values[index] = current;
    }
}
