/**
 * @file io.c
 * @brief Реализация функции для чтения числовой последовательности из файла.
 *
 * Файл должен содержать одну строку с числами, разделёнными пробелами.
 * Используется для обработки входных данных в задачах, где требуется обработать
 * последовательность целых чисел.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "io.h"

int get_seq_len(char* path)
{
    if ( !path )
    {
        fprintf(stderr, " [E] Nullptr в get_seq_len()\n");
        return -1;
    }

    FILE* file = fopen(path, "r");
    if ( !file )
    {
        fprintf(stderr, " [E] Невозможно открыть файл %s\n", path);
        return -2;
    }

    char line[MAX_LINE_LEN];
    fgets(line, sizeof(line), file);
    char* token = strtok(line, " \n\0");

    int i = 0;
    while ( token )
    {
        token = strtok(NULL, " \n\0");
        i++;
    }
    
    return i;
}

int read_seq(char* path, int* result, int size)
{
    if ( !path || !result )
    {
        fprintf(stderr, " [E] Nullptr в read_seq()\n");
        return -1;
    }

    FILE* file = fopen(path, "r");
    if ( !file )
    {
        fprintf(stderr, " [E] Невозможно открыть файл %s\n", path);
        return -2;
    }

    char line[MAX_LINE_LEN];
    fgets(line, sizeof(line), file);
    char* token = strtok(line, " \n\0");

    int i = 0;
    while ( token && i < size )
    {
        result[i++] = atoi(token);
        token = strtok(NULL, " \n\0");
    }

    return 0;
}
