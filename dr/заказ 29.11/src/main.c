#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(void) {
    create_matrix_from_file("file");
    create_matrix(1, 1);
    free_matrix(NULL);

    get_rows(NULL, NULL);
    get_cols(NULL, NULL);
    get_elem(NULL, 1, 1, NULL);
    set_elem(NULL, 1, 1, 1);

    mul_scalar(NULL, 2);
    transp(NULL);

    sum(NULL, NULL);
    sub(NULL, NULL);
    mul(NULL, NULL);

    det(NULL, NULL);
    adj(NULL);
    inv(NULL);
    return 0;
}

