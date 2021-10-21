#include <stdio.h>
#include <stdint.h>

#define N 5

struct stack_t {
    // N lines of up to 200 chars
    char data[N][200];
    int32_t top;
};

// Returns 1 if stack is empty, or
// 0 if stack is not empty.
int32_t stack_empty(const struct stack_t* s) {
    return (N == s->top);
}

void stack_init(struct stack_t* s) {
    s->top = N;
}

// Returns 1 if stack is full, or
// 0 if stack is not full.
int32_t stack_full(const struct stack_t* s) {
    return (0 == s->top);
}

// Returns 1 on success,
// or 0 on failure.
int32_t stack_push(struct stack_t* s, const char* str)
{
    int32_t i;
    char*   write;

    if (stack_full (s)) { 
        return 0;
    }

    write = s->data[--s->top];

    for (i = 0; '\0' != *str; i++) {
        if (199 == i) {
            s->top++;
            return 0; 
        }

        *write++ = *str++;
    }

    *write = '\0';

    return 1;
}

// Returns 1 on success,
// or 0 on failure.
int32_t stack_pop(struct stack_t* s, char* buf, int32_t len)
{
    int32_t i;
    char*   read;

    if (stack_empty (s)) { 
        return 0;
    }

    read = s->data[s->top];

    for (i = 1; len > i && '\0' != *read; i++) {
        *buf++ = *read++;
    }

    *buf = '\0';
    s->top++;

    return 1;
}

int main ()
{
    char buf[200];
    struct stack_t stack;

    stack_init(&stack);

    while (!stack_full (&stack) && NULL != fgets(buf, 200, stdin)) {
        if (!stack_push (&stack, buf)) {
            break;
        }
    }

    while (!stack_empty (&stack)) {
        if (!stack_pop (&stack, buf, 200)) {
            break;
        }
        printf ("%s", buf);
    }

    return 0;
} // end of main
