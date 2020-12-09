#include <iostream>

#include <cstddef>
#include <cstdlib>

#define INIT_SIZE 10
#define MULTIPLIER 1

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

typedef int T;

typedef struct Queue_tag {
    T *data;
    size_t size;
    size_t top;
    size_t head;
} Queue_t;

Queue_t* costructor() {
    Queue_t *out = nullptr;
    out = static_cast<Queue_t *>(malloc(sizeof(Queue_t)));
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

void destructor(Queue_t **stack) {
    free((*stack)->data);
    free(*stack);
    *stack = nullptr;
}


void resize(Queue_t *stack) {
    stack->size += MULTIPLIER;
    stack->data = static_cast<T *>(realloc(stack->data, stack->size * sizeof(T)));
    if (stack->data == nullptr) {
        exit(STACK_OVERFLOW);
    }
}


void push(Queue_t *stack, T value) {
    if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

T pop(Queue_t *stack) {
    if (stack->top == stack->head - 1) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    stack->head++;
    return stack->data[stack->head - 1];
}

size_t get_size(Queue_t *stack) {
    if (stack == nullptr) {
        return -1;
    }

    return stack->size - 1;
}

void print(Queue_t *queue) {
    for (int i = queue->head; i < queue->size; ++i) {
        std::cout << queue->data[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int i;
    Queue_t *s = costructor();

    for (i = 0; i < 12; i++) {
        push(s, i);
    }

    std::cout << "Размер очереди: " << get_size(s) << '\n';

    print(s);

    for (i = 0; i < 12; i++) {
        std::cout << pop(s) << '\n';
    }

    destructor(&s);
}
