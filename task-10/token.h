#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 32
#define MAX_TOKENS 256

// Конвертирует входную строку-выражение в массив лексем
int tokenize(char* input, char** output);
