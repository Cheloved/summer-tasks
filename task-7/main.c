#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1024

long get_file_size(FILE* file)
{
    if ( !file )
    {
        fprintf(stderr, " [E] Невозможно открыть файл!\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size; 
}

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, " [E] Должен быть предоставлен 1 файл для чтения\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "rb");
    if ( !file )
    {
        perror(" [E] Ошибка при чтении файла");
        return -1;
    }

    FILE* out = fopen("out.txt", "wb");
    if ( !out )
    {
        perror(" [E] Ошибка при открытии файла записи");
        return -1;
    }

    // Считывание файла блоками
    char chunk[CHUNK_SIZE]; 
    long file_size = get_file_size(file);
    int chunks_read = 0;
    long left;
    while ( (left = file_size - chunks_read * CHUNK_SIZE) > 0 )
    {
        long to_read = (left / CHUNK_SIZE > 0) ? CHUNK_SIZE : left;
        fread(chunk, sizeof(char), to_read, file);
        fwrite(chunk, sizeof(char), to_read, out);
        chunks_read++;
    }

    fclose(file);
    fclose(out);
    return 0;
}
