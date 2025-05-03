#pragma once

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

#define DEBUG 0

typedef struct
{
    uint32_t iter;      // Текущая глубина разделения (для отладки)
    char*    input;     // Исходный текст
    long* ar;        // Указатель на исходный массив индексов новых строк
    long left_idx;  // Индекс начала среза для текущего потока
    long right_idx; // Индекс конца среза
    long* result;    // Массив, куда будет сохранен результат слияния
} s_data;

void* merge_sort_thread(void* arg);
int merge_sort(char* input, long* array, long length, long* result);
