#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Считывает матрицу из файла
int read_matrix(char* path, int** result, int MAX_ROWS, int MAX_COLS,
                int MAX_LINE_LEN);
