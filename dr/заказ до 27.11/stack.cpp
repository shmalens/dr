#include <iostream>

#include <cstddef>
#include <cstdlib>

#define INIT_SIZE 10
#define MULTIPLIER 1

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

typedef int T;

typedef struct Stack_tag {
    T *data;
    size_t size;
    size_t top;
} Stack_t;

Stack_t* costructor() {
    Stack_t *out = nullptr;
    out = static_cast<Stack_t *>(malloc(sizeof(Stack_t)));
    if (out == nullptr) {
        exit(OUT_OF_MEMORY);
    }
    out->size = INIT_SIZE;
    out->data = static_cast<T *>(malloc(out->size * sizeof(T)));
    if (out->data == nullptr) {
        free(out);
        exit(OUT_OF_MEMORY);
    }
    out->top = 0;
    return out;
}

void destructor(Stack_t **stack) {
    free((*stack)->data);
    free(*stack);
    *stack = nullptr;
}


void resize(Stack_t *stack) {
    stack->size += MULTIPLIER;
    stack->data = static_cast<T *>(realloc(stack->data, stack->size * sizeof(T)));
    if (stack->data == nullptr) {
        exit(STACK_OVERFLOW);
    }
}


void push(Stack_t *stack, T value) {
    if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

T pop(Stack_t *stack) {
    if (stack->top == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    return stack->data[stack->top];
}

int get_size(Stack_t *stack) {
    if (stack == nullptr) {
        return -1;
    }

    return stack->size - 1;
}

void print(Stack_t *stack) {
    for (int i = 0; i < stack->top; ++i) {
        std::cout << stack->data[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int i;
    Stack_t *s = costructor();

    for (i = 0; i < 12; i++) {
        push(s, i);
    }

    std::cout << "Размер стека: " << s->size << '\n';

    print(s);

    for (i = 0; i < 12; i++) {
        std::cout << pop(s) << '\n';
    }

    destructor(&s);
}
