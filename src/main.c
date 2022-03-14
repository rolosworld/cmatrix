#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float** values;
  size_t rows_sz;
  size_t cols_sz;
} CMatrix;

CMatrix* matrix_create(size_t rows, size_t cols) {
  CMatrix* matrix = malloc(sizeof(CMatrix));
  matrix->values = malloc(sizeof(float*) * rows);
  for (matrix->rows_sz = 0; matrix->rows_sz < rows; matrix->rows_sz++) {
      matrix->values[matrix->rows_sz] = malloc(sizeof(float) * cols);
  }

  matrix->cols_sz = cols;
  return matrix;
}

void matrix_free(CMatrix* matrix) {
  while (matrix->rows_sz--) {
    free(matrix->values[matrix->rows_sz]);
  }

  free(matrix->values);
  free(matrix);
}

int matrix_dot_sub(CMatrix* A, CMatrix* B, CMatrix* C, size_t row, size_t col) {
  if (A->rows_sz < row &&
      B->cols_sz < col &&
      A->cols_sz != B->rows_sz) {
    return 0;
  }

  C->values[row][col] = 0;
  for (size_t i = 0; i < A->cols_sz; i++) {
    C->values[row][col] += A->values[row][i] * B->values[i][col];
  }

  return 1;
}

CMatrix* matrix_dot(CMatrix* A, CMatrix* B) {
  CMatrix* C = matrix_create(A->rows_sz, A->cols_sz);

  for (size_t i = 0; i < C->rows_sz; i++) {
    for (size_t j = 0; j < C->cols_sz; j++) {
      matrix_dot_sub(A, B, C, i, j);
    }
  }

  return C;
}

int matrix_transpose_dot_sub(CMatrix* A, CMatrix* C, size_t row, size_t col) {
  if (A->rows_sz < row && A->cols_sz < col) {
    return 0;
  }

  C->values[row][col] = 0;
  for (size_t i = 0; i < A->cols_sz; i++) {
    /* C = At * A */
    C->values[row][col] += A->values[i][row] * A->values[i][col];
  }

  return 1;
}

CMatrix* matrix_transpose_dot(CMatrix* A) {
  CMatrix* C = matrix_create(A->rows_sz, A->cols_sz);

  for (size_t i = 0; i < C->rows_sz; i++) {
    for (size_t j = 0; j < C->cols_sz; j++) {
      matrix_transpose_dot_sub(A, C, i, j);
    }
  }

  return C;
}

void matrix_print(CMatrix* M) {
  for (size_t i = 0; i < M->rows_sz; i++) {
    for (size_t j = 0; j < M->cols_sz; j++) {
      printf("%f ", M->values[i][j]);
    }
    printf("\n");
  }
}

void matrix_transpose_print(CMatrix* M) {
  for (size_t i = 0; i < M->cols_sz; i++) {
    for (size_t j = 0; j < M->rows_sz; j++) {
      printf("%f ", M->values[j][i]);
    }
    printf("\n");
  }
}

int main() {
  CMatrix* m = matrix_create(3 ,3);

  m->values[0][0] = 1;
  m->values[0][1] = 2;
  m->values[0][2] = 3;

  m->values[1][0] = 4;
  m->values[1][1] = 5;
  m->values[1][2] = 6;

  m->values[2][0] = 7;
  m->values[2][1] = 8;
  m->values[2][2] = 9;

  matrix_print(m);

  printf("----\n");

  CMatrix* C = matrix_dot(m, m);
  matrix_print(C);
  printf("----\n");
  matrix_transpose_print(C);

  printf("At*A----\n");
  CMatrix* D = matrix_transpose_dot(m);
  matrix_print(D);


  matrix_free(m);
  matrix_free(C);
  matrix_free(D);
  return 0;
}
