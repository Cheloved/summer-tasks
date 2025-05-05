#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 16384

// Считывает последовательность из файла
int read_seq(char* path, int* result, int size);
