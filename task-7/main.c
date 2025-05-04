#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

int copy_from_to(FILE* from, long file_size, FILE* to)
{
    char chunk[CHUNK_SIZE]; 
    int chunks_read = 0;
    long left;
    while ( (left = file_size - chunks_read * CHUNK_SIZE) > 0 )
    {
        long to_read = (left / CHUNK_SIZE > 0) ? CHUNK_SIZE : left;
        fread(chunk, sizeof(char), to_read, from);
        fwrite(chunk, sizeof(char), to_read, to);
        chunks_read++;
    }

    return 0;
}

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, " [E] Должен быть предоставлен 1 файл для чтения\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    if ( !file )
    {
        perror(" [E] Ошибка при чтении файла");
        return -1;
    }

    long file_size = get_file_size(file);

    pid_t pid = fork();
    if ( pid < 0 )
    {
        fprintf(stderr, " [E] Ошибка при fork()\n");
        return -1;
    }

    FILE* out;
    if ( pid == 0 )
        out = fopen("child_out.txt", "w+");
    else
        out = fopen("parent_out.txt", "w+");

    if ( !out )
    {
        perror(" [E] Ошибка при открытии файла записи");
        return -1;
    }

    copy_from_to(file, file_size, out);
    fseek(out, 0, SEEK_SET);

    if ( pid == 0 )
    {
        printf("Содержимое файла дочернего процесса: \n");
        copy_from_to(out, file_size, stdout);
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("\nСодержимое файла родительского процесса: \n");
        copy_from_to(out, file_size, stdout);
    }

    fclose(file);
    fclose(out);
    return 0;
}
