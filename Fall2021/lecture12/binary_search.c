#include <stdio.h>
#include <inttypes.h>

// function prototype
int32_t binary_search(int32_t array[], int32_t len, int32_t value);

int main() 
{
    int32_t array[10] = { -10, -3, 6, 8, 9, 11, 12, 16, 44, 56 };
    int32_t value, index;

    printf("Enter value you would like to look for in the array: ");
    scanf("%i", &value);

    index = binary_search(array, 10, value);

    if (-1 != index) {
        printf("Value %i was found at index %i\n", value, index);
    } else {
        printf("Value %i does not exist in the array\n", value);
    }

    return 0;
}


// implementation
int32_t binary_search(int32_t array[], int32_t len, int32_t value)
{
    int32_t low = 0;
    int32_t high = len - 1;
    int32_t mid;

    while (high >= low) {

        mid = low + (high - low) / 2;

        // look at one value
        if (value == array[mid]) {
                return mid;  // Found!
        }

        // and adjust bounds
        if (value < array[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}




