#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Считывает матрицу из файла
int read_matrix(char* path, int** result, int MAX_ROWS, int MAX_COLS,
                int MAX_LINE_LEN);

// Генерирует матрицу из случайных значений
int generate_matrix(char* path, int size, int min, int max);
