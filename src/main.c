#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float** values;
  size_t rows_sz;
  size_t cols_sz;
} CMatrix;

void matrix_create(size_t rows, size_t cols, CMatrix* matrix) {
  matrix->values = malloc(sizeof(float*) * rows);
  for (matrix->rows_sz = 0; matrix->rows_sz < rows; matrix->rows_sz++) {
      matrix->values[matrix->rows_sz] = malloc(sizeof(float) * cols);
  }

  matrix->cols_sz = cols;
}

void matrix_free(CMatrix* matrix) {
  while (matrix->rows_sz--) {
    free(matrix->values[matrix->rows_sz]);
  }

  free(matrix->values);
}

int main() {
  CMatrix m;
  matrix_create(3 ,3, &m);
  matrix_free(&m);
  return 0;
}
