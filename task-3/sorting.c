#include "sorting.h"

// Получение размера файла
long get_file_size(char* path)
{
    FILE* file = fopen(path, "rb");
    if ( file == NULL )
    {
        printf(" [E] Невозможно открыть файл %s!\n", path);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fclose(file);
    return size;
}

// Считывает содержимое файла
int read_file(char* path, long size, char* result)
{
    FILE* file = fopen(path, "rb");
    if ( file == NULL )
    {
        printf(" [E] Невозможно открыть файл %s!\n", path);
        return -1;
    }

    size_t bytes = fread(result, 1, size, file);
    result[bytes] = 0;

    fclose(file);
    return 0;
}

// Возвращает количество непустых строк
int get_lines_count(char* input, long size)
{
    int count = 0;
    int visible_found = 0;
    for ( long i = 0; i < size+1; i++ )
    {
        if ( (input[i] == '\n' || input[i] == 0) && visible_found )
        {
            count++;
            visible_found = 0;
            continue;
        }

        if ( input[i] != ' ' )
            visible_found = 1;
    }

    return count;
}

// Возвращает массив индексов на начало непустых строк
int get_indexes(char* input, long size, long* result)
{
    int count = 0;
    int start_idx = 0;
    int visible_found = 0;
    for ( long i = 0; i < size+1; i++ )
    {
        if ( input[i] == '\n' || input[i] == 0 )
        {
            if ( visible_found )
                result[count++] = start_idx;

            start_idx = i+1;
            visible_found = 0;
            continue;
        }

        if ( input[i] != ' ' )
            visible_found = 1;
    }

    return 0;
}
