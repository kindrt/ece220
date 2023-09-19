#include <stdio.h>
#include <stdint.h>

/* function prototype */
int32_t min_value(int32_t const values[], int32_t n_values);

int main()
{
    int32_t my_nums[4] = {93, 100, 79, 42};
    int32_t least;

    least = min_value (my_nums, 4);

    printf("Min value is %d\n", least);

    return 0;
}

/* function implementation */
int32_t min_value(int32_t const values[], int32_t n_values)
{
    int32_t min = values[0];
    int32_t check;

    for (check=1; n_values > check; check++) {
        if (min > values[check]) {
            min = values[check];
        }
    }

    return min;
}
