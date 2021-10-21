#include <stdio.h>
#include <stdint.h>

struct one_t {
    int8_t a1;
    int8_t a2;

    int32_t b;
};

int main() 
{
    printf("size of int8_t = %li\n", sizeof(int8_t));
    printf("size of int32_t = %li\n", sizeof(int32_t));
    printf("size of struct one_t = %li\n", sizeof(struct one_t));

    return 0;
}