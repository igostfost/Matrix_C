# s21_matrix
Реализация библиотеки matrix.h.

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
    2.1. [Information](#information)
3. [Chapter III](#part-1-реализация-функции-библиотеки-matrixh)  


## Introduction

В данном проекте реализована своя библиотека для обработки числовых матриц на языке программирования Си. Матрицы являются одной из базовых структур данных в программировании, например, они применяются для представления табличных значений, для вычислительных задач и нейронных сетей. В рамках этого проекта предполагается более детальное знакомство с матрицами и закрепление структурного подхода.  


# Chapter II

### Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Операции над матрицами

Все операции (кроме сравнения матриц) должны возвращать результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

### Создание матриц (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Очистка матриц (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Сравнение матриц (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

Две матрицы A, B совпадают |A = B|, если совпадают их размеры и соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).

Сравнение должно происходить вплоть до 7 знака после запятой включительно.


## Реализация функции библиотеки matrix.h

Реализовать основные действия с матрицами (частично описанные [выше](#операции-над-матрицами)): create_matrix (создание), remove_matrix (очистка и уничтожение), eq_matrix (сравнение), sum_matrix (сложение), sub_matrix (вычитание), mult_matrix (умножение), mult_number (умножение на число), transpose (транспонирование), determinant (вычисление определителя), calc_complements (вычисление матрицы алгебраических дополнений), inverse_matrix (поиск обратной матрицы). 

- Библиотека должна быть разработана на языке Си стандарта C11 с использованием компилятора gcc 
- Код библиотеки должен находиться в папке src в ветке develop  
- Не использовать устаревшие и выведенные из употребления конструкции языка и библиотечные функции. Обращать внимания на пометки legacy и obsolete в официальной документации по языку и используемым библиотекам. Ориентироваться на стандарт POSIX.1-2017
- При написании кода необходимо придерживаться Google Style
- Оформить решение как статическую библиотеку (с заголовочным файлом s21_matrix.h)
- Библиотека должна быть разработана в соответствии с принципами структурного программирования
- Перед каждой функцией использовать префикс s21_
- Подготовить полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check
- Unit-тесты должны покрывать не менее 80% каждой функции
- Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix.a, gcov_report)
- В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с флагами gcov 
- Матрица должна быть реализована в виде структуры описанной [выше](#структура-матрицы-на-языке-c) 
- Проверяемая точность дробной части - максимум 6 знаков после запятой.


### ENG

### Matrix structure in C language:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```
## Matrix operations

All operations (except matrix comparison) should return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

### Creating matrices (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Cleaning of matrices (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Matrix comparison (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

The matrices A, B are equal |A = B| if they have the same dimensions and the corresponding elements are identical, thus for all i and j: A(i,j) = B(i,j)

The comparison must be up to and including 7 decimal places.


## Implementation of the matrix.h library functions

Implement basic operations with matrices (partially described [above](#matrix-operations)): create_matrix (creation), remove_matrix (cleaning and destruction), eq_matrix (comparison), sum_matrix (addition), sub_matrix (subtraction), mult_matrix (multiplication), mult_number (multiplication by number), transpose (transpose), determinant (calculation of determinant), calc_complements (calculation of matrix of algebraic complements), inverse_matrix (finding inverse of the matrix).

- The library must be developed in C language of C11 standard using gcc compiler
- The library code must be located in the src folder on the develop branch   
- Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard.
- When writing code it is necessary to follow the Google style
- Make it as a static library (with the s21_matrix.h header file)
- The library must be developed according to the principles of structured programming;
- Use prefix s21_ before each function
- Prepare full coverage of library functions code with unit-tests using the Check library
- Unit tests must cover at least 80% of each function (checked using gcov)  
- Provide a Makefile for building the library and tests (with targets all, clean, test, s21_matrix.a, gcov_report)
- The gcov_report target should generate a gcov report in the form of an html page. Unit tests must be run with gcov flags to do this 
- The matrix must be implemented as the structure described [above](#matrix-structure-in-c-language)
- Verifiable accuracy of the fractional part is up to 6 decimal places
