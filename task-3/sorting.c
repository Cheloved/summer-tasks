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
