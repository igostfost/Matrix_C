#include "s21_matrix.h"

void creat_matrix(int rows, int columns, double *arr, matrix_t *result) {
  s21_create_matrix(rows, columns, result);
  int arr_index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = arr[arr_index];
      arr_index++;
    }
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 0;
  result->rows = rows;
  result->columns = columns;
  if (rows < 1 || columns < 1) flag = 1;
  result->matrix = calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
  }
  return flag;
}

void s21_remove_matrix(matrix_t *arr) {
  for (int i = 0; i < arr->rows; i++) {
    free(arr->matrix[i]);
  }
  free(arr->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 0;
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabsl(A->matrix[i][j] - B->matrix[i][j]) >= MIN_EPS) {
          flag = 1;
        }
      }
    }
  } else {
    flag = 1;
  }
  return flag ? FAILURE : SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    flag = 1;
  }
  flag = s21_create_matrix(A->rows, A->columns, result);
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    flag = 2;
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    flag = 1;
  }
  flag = s21_create_matrix(A->rows, A->columns, result);
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    flag = 2;
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;
  if (A->columns < 1 || A->rows < 1) {
    flag = 1;
  } else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    flag = 1;
  }
  if (flag == 0) {
    flag = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int q = 0; q < A->columns; q++) {
          result->matrix[i][j] =
              result->matrix[i][j] + A->matrix[i][q] * B->matrix[q][j];
        }
      }
    }
  } else {
    flag = 2;
  }

  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return 0;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = 0;
  if (A->rows != A->columns) {
    flag = 2;
  }
  if (A->columns == 1 && flag == 0) {
    *result = A->matrix[0][0];
  }
  if (A->columns == 2 && flag == 0) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  }
  if (A->columns > 2 && flag == 0) {
    int flag_minus = 1;
    double determinant = 0;
    for (int i = 0; i < A->columns; i++) {
      double tmp_determ = 0;
      matrix_t mini_matrix;
      delete_rows_and_columns(*A, &mini_matrix, 0, i);
      s21_determinant(&mini_matrix, &tmp_determ);
      determinant = determinant + flag_minus * A->matrix[0][i] * tmp_determ;
      s21_remove_matrix(&mini_matrix);
      flag_minus = flag_minus * -1;
    }
    *result = determinant;
  }

  return flag;
}

void delete_rows_and_columns(matrix_t origin, matrix_t *result, int delete_rows,
                             int delete_columns) {
  s21_create_matrix(origin.rows - 1, origin.columns - 1, result);
  for (int i = 0, q = 0; i < origin.rows; i++) {
    if (i == delete_rows) {
      continue;
    }
    for (int j = 0, w = 0; j < origin.columns; j++) {
      if (j == delete_columns) {
        continue;
      }
      result->matrix[q][w] = origin.matrix[i][j];
      w++;
    }
    q++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->columns != A->rows) {
    flag = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t mini_matrix;
        double num = 0;
        delete_rows_and_columns(*A, &mini_matrix, i, j);
        s21_determinant(&mini_matrix, &num);
        s21_remove_matrix(&mini_matrix);
        result->matrix[i][j] = num * pow(-1, i + j);
      }
    }
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->columns < 1 || A->rows < 1) {
    flag = 1;
  } else {
    double determinant = 0;
    flag = s21_determinant(A, &determinant);
    if (determinant == 0) {
      flag = 1;
    }
    if (flag == 0) {
      matrix_t minors, revers;
      s21_calc_complements(A, &minors);
      s21_transpose(&minors, &revers);
      s21_mult_number(&revers, 1 / determinant, result);
      s21_remove_matrix(&minors);
      s21_remove_matrix(&revers);
    }
  }
  return flag;
}
