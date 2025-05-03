#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bubble.h"
#include "merge.h"
#include "utils.h"

// Получение размера файла
long get_file_size(char* path);

// Считывает содержимое файла
int read_file(char* path, long size, char* result);

// Возвращает количество непустых строк
int get_lines_count(char* input, long size);

// Возвращает массив индексов на начало непустых строк
int get_indexes(char* input, long size, long* result);

// Проверяет доступность способа сортировки
int method_available(char* method);

// Сортирует файл input способом method и записывает в output
int sort_file(char* input, char* output, char* method);
