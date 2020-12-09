#include <iostream>
#include <cstddef>
#include <cstdlib>

typedef int T;

typedef struct _Node {
    T data;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct _Ring {
    size_t size;
    Node *current;
    Node *head;
    Node *tail;
} Ring;

Node* next(Ring *ring) {
    Node* retVal = nullptr;
    if (ring->current) {
        ring->current = ring->current->next;
        retVal = ring->current;
    }
    return retVal;
}

Node* prev(Ring *ring) {
    Node* retVal = nullptr;
    if (ring->current) {
        ring->current = ring->current->prev;
        retVal = ring->current;
    }
    return retVal;
}

Ring* constructor() {
    Ring *tmp = (Ring*)malloc(sizeof(Ring));

    tmp->size = 0;
    tmp->current = nullptr;

    return tmp;
}

void add_tail(Ring *ring, T value) {
    Node *prev = nullptr;
    Node *tmp = (Node*)malloc(sizeof(Node));

    tmp->data = value;
    //Если в кольце нет элементов
    if (ring->current == nullptr) {
        ring->current = tmp;
        ring->head = tmp;
        ring->tail = tmp;
        tmp->next = tmp->prev = tmp;
    } else {
        prev = ring->current->next->prev;
        tmp->next = ring->current->next;
        tmp->prev = ring->current;
        prev->prev = tmp;
        ring->current->next = tmp;
        ring->current = tmp;
        ring->tail = tmp;
        ring->head->prev = ring->tail;
    }
    ring->size++;
}

void add_head(Ring *ring, T value) {
    Node *prev = nullptr;
    Node *tmp = (Node*)malloc(sizeof(Node));


    tmp->next = ring->head;
    tmp->prev = ring->tail;
    tmp->data = value;

    ring->tail->next = tmp;
    ring->head->prev = tmp;

    ring->head = tmp;
    ring->current = tmp;
    ring->size++;
}

void insert_ptr(Node *node, T value) {
    Node *tmp = (Node*)malloc(sizeof(Node));

    tmp->next = node->next;
    tmp->prev = node;
    tmp->data = value;

    node->next->prev = tmp;
    node->next = tmp;
}

void insert(Ring *ring, unsigned int i, T value) {
    if(i > ring->size) {
        return;
    }


    for (int j = 0; j < i - 2; ++j) {
        next(ring);
    }
    Node *prev = next(ring);
    insert_ptr(prev, value);

    ring->current = ring->head;
    ring->size++;
}

T remove_ptr(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    T retVal = node->data;


    free(node);
    return retVal;
}

T remove_id(Ring *ring, unsigned int i) {
    if(i > ring->size) {
        exit(1);
    }


    for (int j = 0; j < i - 1; ++j) {
        next(ring);
    }
    Node *prev = next(ring);

    ring->current = ring->head;
    ring->size--;
    return remove_ptr(prev);
}

T remove_head(Ring *ring) {
    Node *afterTarget = nullptr;
    T retVal;

    if (ring->current == nullptr) {
        exit(1);
    }

    //Если в кольце последний элемент
    if (ring->current->next == ring->current) {
        retVal = ring->current->data;
        free(ring->current);
        ring->current = nullptr;
    } else {
        afterTarget = ring->current->next;
        ring->current->prev->next = afterTarget;
        afterTarget->prev = ring->current->prev;
        retVal = ring->current->data;
        free(ring->current);
        ring->current = afterTarget;
        ring->head = ring->current;
    }
    ring->size--;
    return retVal;
}

T remove_tail(Ring *ring) {
    T retVal;

    if (ring->current == nullptr) {
        exit(1);
    }

    Node *tmp = ring->tail;

    ring->tail = tmp->prev;
    ring->tail->next = ring->head;
    ring->head->prev = tmp->prev;

    retVal = tmp->data;
    free(tmp);

    ring->size--;
    return retVal;
}

int destructor(Ring *ring) {
    if (ring == nullptr) {
        return 0;
    }

    do {
        remove_head(ring);
    } while (ring->size != 0);

    return 1;
}

void circle(const Ring *ring, void (*f)(Node* node)) {
    Node *anchor = ring->current;
    if (anchor) {
        do {
            f(anchor);
            anchor = anchor->next;
        } while (anchor != ring->current);
    }
}

void printNode(Node *node) {
    std::cout << node->data << ' ';
}

size_t get_size(Ring *ring) {
    return ring->size;
}

T get_by_id(Ring *ring, unsigned int i) {
    if(i > ring->size) {
        exit(1);
    }


    if (i == 0) {
        return ring->head->data;
    }

    for (int j = 0; j < i - 1; ++j) {
        next(ring);
    }
    Node *prev = next(ring);

    ring->current = ring->head;
    return prev->data;
}

int find_by_val(Ring *ring, T val) {
    Node *tmp = ring->head;

    for (int j = 0; j < ring->size; ++j) {
        if(tmp->data == val) {
            return j;
        }
        tmp = tmp->next;
    }

    return -1;
}

int main() {
    Ring *r = constructor();

    add_tail(r, 1);
    add_tail(r, 2);
    add_tail(r, 3);
    add_tail(r, 4);

    circle(r, printNode);
    std::cout << "Размер: " << get_size(r) << '\n';

    add_head(r, 5);
    add_head(r, 6);
    add_head(r, 7);

    circle(r, printNode);
    std::cout << "Размер: " << get_size(r) << '\n';

    std::cout << "Val 5 at index " << find_by_val(r, 5) << '\n';

    insert(r, 4, 0);
    circle(r, printNode);
    std::cout << '\n';

    std::cout << remove_head(r) << ' ' << remove_head(r) << '\n';
    circle(r, printNode);
    std::cout << "Размер: " << get_size(r) << '\n';

    std::cout << remove_tail(r) << '\n';
    circle(r, printNode);
    std::cout << "Размер: " << get_size(r) << '\n';

    std::cout << remove_id(r, 3) << '\n';
    circle(r, printNode);
    std::cout << "Размер: " << get_size(r) << '\n';

    std::cout << "Getting by id: " << get_by_id(r, 3) << ' ' << get_by_id(r, 0) << '\n';



    destructor(r);
    return 0;
}
