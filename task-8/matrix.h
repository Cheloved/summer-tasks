#pragma once

#include <stdio.h>

#include "reading.h"

extern int global_i;
extern int global_j;

// Инициализация динамической матрицы
int** init_mat_square(int size);

// Умножение матриц
int matrix_multiply_square(int size, int** a, int** b, int** result);

// Вывод матрицы
void print_mat(int** mat, int size);
