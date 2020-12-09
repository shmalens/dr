#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

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

Matrix* create_matrix_from_file(const char* pathFile) {
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

int get_rows(const Matrix* matrix, size_t* rows) {
        if (rows == NULL || matrix == NULL) {
                return -1;
        }
        *rows = matrix->amountRow;
        return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
        if (cols == NULL || matrix == NULL) {
                return -1;
        }
        *cols = matrix->amountCol;
        return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
        if (matrix == NULL || val == NULL) {
                return -1;
        }

        if  ((row > matrix->amountRow - 1) ||
            (col > matrix->amountCol - 1)) {
                return -1;
        }

        *val = matrix->matrixData[row][col];
        return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
        if (matrix == NULL) {
                return -1;
        }

        if  ((row > matrix->amountRow - 1) ||
            (col > matrix->amountCol - 1)) {
                return -1;
        }

        matrix->matrixData[row][col] = val;
        return 0;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
         if (matrix == NULL) {
                 return NULL;
         }

         Matrix *resMatrix = create_matrix(matrix->amountRow, matrix->amountCol);
         if (resMatrix == NULL) {
             return NULL;
         }

         for (size_t i = 0; i < resMatrix->amountRow; ++i) {
                 for (size_t j = 0; j < resMatrix->amountCol; ++j) {
                         resMatrix->matrixData[i][j] = matrix->matrixData[i][j] * val;
                 }
         }
         return resMatrix;
}

Matrix* transp(const Matrix* matrix) {
         if (matrix == NULL) {
                 return NULL;
         }

         Matrix *resMatrix = create_matrix(matrix->amountCol, matrix->amountRow);
         if (resMatrix == NULL) {
                 return NULL;
         }

         for (size_t i = 0; i < matrix->amountRow; ++i) {
                 for (size_t j = 0; j < matrix->amountCol; ++j) {
                         resMatrix->matrixData[j][i] = matrix->matrixData[i][j];
                 }
         }
         return resMatrix;
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

Matrix* sub(const Matrix* l, const Matrix* r) {
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
                        resMatrix->matrixData[i][j] = l->matrixData[i][j] - r->matrixData[i][j];
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

static Matrix *alg_coml(size_t indexRow, size_t indexCol, Matrix *matrix) {
        Matrix *resMatrix = create_matrix(matrix->amountRow - 1, matrix->amountCol - 1);
        if (resMatrix == NULL) {
                return NULL;
        }

        int tmpJ = 0;
        int tmpI = 0;

        for (size_t i = 0; i < matrix->amountRow; ++i) {
                if (i != indexRow) {
                        tmpJ = 0;
                        for (size_t j = 0; j < matrix->amountCol; ++j) {
                                if (j != indexCol) {
                                        resMatrix->matrixData[tmpI][tmpJ] = matrix->matrixData[i][j];
                                        ++tmpJ;
                                }
                        }
                        ++tmpI;
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

Matrix *adj(const Matrix *matrix) {
        if (matrix == NULL) {
                return NULL;
        }

        if (matrix->amountRow != matrix->amountCol) {
                return NULL;
        }

        Matrix *resMatrix = create_matrix(matrix->amountRow, matrix->amountCol);
        if (resMatrix == NULL) {
                return NULL;
        }

        double val = 0;
        for (size_t i = 0; i < resMatrix->amountRow; ++i) {
                for (size_t j = 0; j < resMatrix->amountCol; ++j) {
                        val = 0;
                        Matrix *transpMatrix = transp(matrix);
                        if (transpMatrix == NULL) {
                                return NULL;
                        }

                        Matrix *algComplMatrix = alg_coml(i, j, transpMatrix);
                        if (algComplMatrix == NULL) {
                                return NULL;
                        }

                        if (det(algComplMatrix, &val) == -1) {
                                free_matrix(algComplMatrix);
                                free_matrix(transpMatrix);
                                return NULL;
                        }

                        resMatrix->matrixData[i][j] = sign_val(i + j) * val;
                        free_matrix(transpMatrix);
                        free_matrix(algComplMatrix);
                }
        }
        return resMatrix;
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

Matrix *inv(const Matrix *matrix) {
        if (matrix == NULL) {
                return NULL;
        }

        if (matrix->amountRow != matrix->amountCol) {
                return NULL;
        }

        double detM = 0;
        det(matrix, &detM);  // Usage only valid pointer and square matrix;

        if (matrix->amountRow == 1) {
                Matrix *resMatrix = create_matrix(matrix->amountRow, matrix->amountCol);
                if (resMatrix == NULL) {
                        return NULL;
                }

                resMatrix->matrixData[0][0] = 1 / matrix->matrixData[0][0];
                return resMatrix;
        }

        if (detM == 0) {
                return NULL;
        }

        Matrix *helpMatrix = adj(matrix);
        if (helpMatrix == NULL) {
                return NULL;
        }

        Matrix *resMatrix = mul_scalar(helpMatrix, 1/detM);
        if (resMatrix == NULL) {
                return NULL;
        }

        free_matrix(helpMatrix);
        return resMatrix;
}
