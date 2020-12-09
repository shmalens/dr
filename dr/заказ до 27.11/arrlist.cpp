#include <iostream>

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101

#define MAX_SIZE 20

typedef int T;


typedef struct Stack_tag {
    T data[MAX_SIZE];
    size_t size;
} list_t;

void init(list_t *lst) {
    lst->size = 0;
}

void destruct(list_t *lst) {
    lst->size = 0;
}

void push(list_t *stack, const T value) {
    if (stack->size >= MAX_SIZE) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}

void push(list_t *lst, unsigned int i, const T value) {
    if (i > lst->size || lst->size > MAX_SIZE - 1) {
        exit(-1);
    }

    for (int j = lst->size - 1; j >= i; --j) {
        lst->data[j + 1] = lst->data[j];
    }
    lst->data[i] = value;
    lst->size++;
}

T pop_beg(list_t *list) {
    T tmp = list->data[0];

    for (int i = 0; i < list->size; ++i) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
    return tmp;
}

T pop(list_t *stack) {
    if (stack->size == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->size--;
    return stack->data[stack->size];
}

T pop(list_t *list, unsigned int i) {
    if (i > list->size) {
        exit(-1);
    }

    T tmp = list->data[i];

    for (unsigned int j = i; j < list->size; ++j) {
        list->data[j] = list->data[j + 1];
    }

    list->size--;
    return tmp;
}

size_t get_size(list_t *lst) {
    return lst->size;
}

T get_by_id(list_t *list, unsigned int i) {
    if (i > list->size) {
        exit(-1);
    }

    return list->data[i];
}

int find_by_val(list_t *list, T val) {
    for (int i = 0; i < list->size; ++i) {
        if (val == list->data[i]) {
            return i;
        }
    }

    return -1;
}

void print(const list_t *list) {
    for (int i = 0; i < list->size; i++) {
        std::cout << list->data[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    list_t stack;
    init(&stack);

    for (int i = 0; i < 18; ++i) {
        push(&stack, i);
    }
    push(&stack, 11, 5);

    std::cout << stack.size << '\n';
    print(&stack);

    pop_beg(&stack);
    pop_beg(&stack);
    pop(&stack, 0);
    pop(&stack, 0);
    print(&stack);

    std::cout << find_by_val(&stack, 7) << '\n';

    destruct(&stack);
    return 0;
}
