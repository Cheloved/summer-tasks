#pragma once

#include <string.h>

// Считывает содержимое файла
int read_file(char* path, char* result);

// Возвращает массив индексов на начало строк
int get_indexes(char* input);

// Проверяет доступность способа сортировки
int method_available(char* method);

// Сортирует файл input способом method и записывает в output
int sort_file(char* input, char* output, char* method);
