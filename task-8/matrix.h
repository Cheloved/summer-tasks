#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int global_row;
extern int global_col;

// Инициализация динамической матрицы
int** init_mat_square(int size);

// Освобождение памяти
int free_mat_square(int** mat, int size);

// Умножение матриц
int matrix_multiply_square(int size, int** a, int** b, int** result);

// Вывод матрицы
void print_mat(int** mat, int size);
