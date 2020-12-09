#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


typedef struct Matrix {
        double **matrixData;

        size_t amountRow;
        size_t amountCol;
} Matrix;

#define SUM_RES "sumres"
#define MUL_RES "mulres"

int free_matrix(Matrix *matrix) {
        if (matrix == NULL) {
            return 0;
        }

        for (size_t i = 0; i < matrix->amountRow; ++i) {
                free(matrix->matrixData[i]);
                matrix->matrixData[i] = NULL;
        }
        free(matrix->matrixData);
        matrix->matrixData = NULL;
        free(matrix);
        return 0;
}

int print_matrix(Matrix* matrix, FILE *fd) {
    if (matrix == NULL) {
        return -1;
    }

    fprintf(fd, "%ld %ld\n", matrix->amountRow, matrix->amountCol);
    for (size_t i = 0; i < matrix->amountRow; ++i) {
        for (size_t j = 0; j < matrix->amountCol; ++j) {
            fprintf(fd, "%f ", matrix->matrixData[i][j]);
        }
        fprintf(fd, "\n");
    }
    printf("\n");
    return 0;
}

static Matrix *matrix_creator(size_t row, size_t col) {
        if (row == 0 || col == 0) {
                return NULL;
        }

        Matrix *matrix = malloc(sizeof(Matrix));
        if (matrix == NULL) {
                return NULL;
        }

        matrix->amountRow = row;
        matrix->amountCol = col;

        matrix->matrixData = malloc(sizeof(double*) * matrix->amountRow);
        if (matrix->matrixData == NULL) {
                free(matrix);
                return NULL;
        }

        for (size_t i = 0; i < matrix->amountRow; ++i) {
                matrix->matrixData[i] = malloc(sizeof(double) * matrix->amountCol);
                if (matrix->matrixData[i] == NULL) {
                        for (size_t j = 0; j < i; ++j) {
                                free(matrix->matrixData[j]);
                        }
                        free(matrix->matrixData);
                        free(matrix);
                        return NULL;
                }
        }
        return matrix;
}

Matrix* create_matrix_from_file(char* pathFile) {
        FILE *file = fopen(pathFile, "r");
        if (file == NULL) {
                return NULL;
        }

        int tmpRow = 0;
        int tmpCol = 0;
        if (fscanf(file, "%d %d", &tmpRow, &tmpCol) != 2) {
                fclose(file);
                return NULL;
        }

        Matrix *matrix = matrix_creator(tmpRow, tmpCol);
        if (matrix == NULL) {
                fclose(file);
                return NULL;
        }
        for (size_t i = 0; i < matrix->amountRow; ++i) {
                for (size_t j = 0; j < matrix->amountCol; ++j) {
                        if (fscanf(file, "%lf", &matrix->matrixData[i][j]) != 1) {
                                free_matrix(matrix);
                                fclose(file);
                                return NULL;
                        }
                }
        }

        fclose(file);
        return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
        Matrix *matrix = matrix_creator(rows, cols);

        if (matrix == NULL) {
                return NULL;
        }

        for (size_t i = 0; i < matrix->amountRow; ++i) {
                for (size_t j = 0; j < matrix->amountCol; ++j) {
                        matrix->matrixData[i][j] = 0;
                }
        }

        return matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
        if (l == NULL || r == NULL) {
                return NULL;
        }

        if (l->amountRow != r->amountRow || l->amountCol != r->amountCol) {
                 return NULL;
        }

        Matrix *resMatrix = create_matrix(l->amountRow, l->amountCol);
        if (resMatrix == NULL) {
                return NULL;
        }

        for (size_t i = 0; i < resMatrix->amountRow; ++i) {
                for (size_t j = 0; j < resMatrix->amountCol; ++j) {
                          resMatrix->matrixData[i][j] = l->matrixData[i][j] + r->matrixData[i][j];
                }
        }
        return resMatrix;
}

static double matrix_mul_elem(const Matrix *l, const Matrix *r, int coord1, int coord2) {
        double tmp = 0;
        for (size_t i = 0; i < l->amountCol; ++i) {
                tmp += l->matrixData[coord1][i] * r->matrixData[i][coord2];
        }
        return tmp;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
        if (l == NULL || r == NULL) {
                return NULL;
        }

        if (l->amountCol != r->amountRow) {
                return NULL;
        }

        Matrix *resMatrix = create_matrix(l->amountRow, r->amountCol);
        if (resMatrix == NULL) {
                return NULL;
        }

        for (size_t i = 0; i < resMatrix->amountRow; ++i) {
                for (size_t j = 0; j < resMatrix->amountCol; ++j) {
                        resMatrix->matrixData[i][j] = matrix_mul_elem(l, r, i, j);
            }
        }
        return resMatrix;
}

static double sign_val(int digit) {
        if ((digit % 2) == 0) {
                return 1;
        } else {
                return -1;
        }
}

static Matrix *get_less_mtrx(size_t indexCol, const Matrix* matrix) {
        Matrix *resMatrix = create_matrix(matrix->amountRow - 1, matrix->amountCol - 1);
        if (resMatrix == NULL) {
                return NULL;
        }

        int tmpJ = 0;

        for (size_t i = 1; i < matrix->amountRow; ++i) {
                for (size_t j = 0; j < matrix->amountCol; ++j) {
                        if (j != indexCol) {
                                resMatrix->matrixData[i - 1][tmpJ] = matrix->matrixData[i][j];
                                ++tmpJ;
                        }
                }
                tmpJ = 0;
        }
        return resMatrix;
}

double determinant(const Matrix *matrix) {
            if (matrix->amountRow == 1) {
                    double val = matrix->matrixData[0][0];
                    return val;
            }

            double result = 0;
            for (size_t i = 0; i < matrix->amountCol; ++i) {
                    Matrix *helpMatrix = get_less_mtrx(i, matrix);
                    if (helpMatrix == NULL) {
                        exit(-1);
                    }
                    result += sign_val(i) * matrix->matrixData[0][i] * determinant(helpMatrix);
                    free_matrix(helpMatrix);
            }
            return result;
}

int det(const Matrix *matrix, double *val) {
        if (matrix == NULL || val == NULL) {
                return -1;
        }

        if (matrix->amountRow != matrix->amountCol) {
                return -1;
        }
        *val = determinant(matrix);
        return 0;
}

static Matrix *get_minor(size_t row, size_t col, int curr_rang, const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix *resMatrix = create_matrix(curr_rang, curr_rang);
    for (size_t i = row; i < curr_rang + row; ++i) {
        for (size_t j = col; j < curr_rang + row; ++j) {
            resMatrix->matrixData[i - row][j - col] = matrix->matrixData[i][j];
        }
    }
    return resMatrix;
}

size_t rang(const Matrix *matrix) {
    if (matrix == NULL) {
        return -1;
    }
    size_t max_rang = (matrix->amountCol <= matrix->amountRow ? matrix->amountCol : matrix->amountRow);

    size_t k = 1;
    double determ;
    while (k < max_rang) {
        int id = 0;
        for (size_t i = 0; i + k - 1 < matrix->amountRow; ++i) {
            for (size_t j = 0; j + k - 1 < matrix->amountCol; ++j) {
                Matrix *curr = get_minor(i, j, k, matrix);
                det(curr, &determ);
                if (determ == 0) {
                    id = 1;
                }
                free_matrix(curr);
            }
        }
        if (id == 0) {
            return k;
        }
        ++k;
    }
    return max_rang;
}


int main(void) {
    char file1[100]; // сюда будем буфферить названия файлов
    char file2[100];
    printf("Введите название первого файла с матрицей для сложения: ");
    scanf("%s", file1); // читаем файл 1
    printf("Введите названия второго файла с матрицей для сложения: ");
    scanf("%s", file2); // читаем файл 2
    Matrix *matrix_mul; // матрица для суммы
    Matrix *matrix_sum; // матрица для умножения
    Matrix *det_matrix; // матрица из которой будем считать детерминант
    FILE *fd; // дескриптор
    double determ;

    Matrix *matrix1 = create_matrix_from_file(file1); // создаем матрицу
    Matrix *matrix2 = create_matrix_from_file(file2); // создаем еще одну

    matrix_sum = sum(matrix1, matrix2); // складываем матрицы
    fd = fopen(SUM_RES, "w"); // записываем в файл
    print_matrix(matrix_sum, fd);
    fclose(fd); // закрываем дескриптор

    free_matrix(matrix1);
    free_matrix(matrix2); // чистим память из под матрицы


    // для остального аналогично
    printf("Введите название первого файла с матрицей для умножения: ");
    scanf("%s", file1);
    printf("Введите названия второго файла с матрицей для умножения: ");
    scanf("%s", file2);

    matrix1 = create_matrix_from_file(file1);
    matrix2 = create_matrix_from_file(file2);

    matrix_mul = mul(matrix1, matrix2);
    fd = fopen(MUL_RES, "w");
    print_matrix(matrix_mul, fd);
    fclose(fd);


    printf("Введите название файла c матрицей для вычисления определителя: ");
    scanf("%s", file1);
    det_matrix = create_matrix_from_file(file1);
    det(det_matrix, &determ);
    free_matrix(det_matrix);

    printf("Определитель матрицы: %f\n", determ);

    free_matrix(matrix1);
    free_matrix(matrix2);


    printf("Введите название файла c матрицей для вычисления ранга: ");
    scanf("%s", file1);
    Matrix *rang_matrix = create_matrix_from_file(file1);
    printf("Ранг матрицы: %ld\n", rang(rang_matrix));

    free_matrix(rang_matrix);
    free_matrix(matrix_sum);
    free_matrix(matrix_mul);
    return 0;
}

