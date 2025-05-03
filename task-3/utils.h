#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Получает длину строки
int get_line_len(char* input, long idx);

// Сравнивает 2 строки от input[a] и input[b] до \n или \0
int linecmp(char* input, long a, long b);

// Соединяет индекс строк в один буффер
int lines_concat(char* input, int lines, long* idxs, char* buffer);
