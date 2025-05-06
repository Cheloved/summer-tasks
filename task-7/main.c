/**
 * @file main.c
 * @brief Пример использования системного вызова fork() и копирования содержимого файла.
 *
 * Программа:
 * - принимает путь к файлу в аргументах командной строки,
 * - запускает дочерний процесс через `fork()`,
 * - оба процесса (родительский и дочерний) читают файл и записывают его содержимое в разные выходные файлы,
 * - затем выводят это содержимое на экран.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @def CHUNK_SIZE
 * @brief Размер порции данных, считываемых/записываемых за один раз.
 */
#define CHUNK_SIZE 1024

/**
 * @brief Получает размер файла в байтах.
 *
 * Перемещает указатель файла в конец, получает позицию (размер),
 * затем возвращает указатель в начало файла.
 *
 * @param file Указатель на открытый файл.
 * @return Размер файла в байтах или -1 при ошибке.
 */
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

/**
 * @brief Копирует данные из одного файла в другой по частям.
 *
 * Использует буфер фиксированного размера (`CHUNK_SIZE`) для последовательного
 * чтения и записи данных. Операция завершается после копирования указанного объема данных.
 *
 * @param from Указатель на исходный файл.
 * @param file_size Общий объем данных для копирования (в байтах).
 * @param to Указатель на целевой файл.
 * @return Возвращает 0 при успешном завершении.
 */
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

/**
 * @brief Точка входа программы.
 *
 * Создаёт дочерний процесс с помощью `fork()`. Родительский и дочерний процессы
 * независимо копируют содержимое файла в свои собственные выходные файлы.
 * После завершения дочернего процесса родитель выводит содержимое обоих файлов.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки. Должен содержать путь к одному файлу.
 * @return Возвращает 0 при успешном завершении или соответствующий код ошибки в случае неудачи.
 */
int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, " [E] Должен быть предоставлен 1 файл для чтения\n");
        return 1;
    }

    pid_t pid = fork();
    if ( pid < 0 )
    {
        fprintf(stderr, " [E] Ошибка при fork()\n");
        return 3;
    }

    FILE* file = fopen(argv[1], "r");
    if ( !file )
    {
        perror(" [E] Ошибка при чтении файла");
        return 2;
    }

    long file_size = get_file_size(file);

    FILE* out;
    if ( pid == 0 )
        out = fopen("child_out.txt", "w+");
    else
        out = fopen("parent_out.txt", "w+");

    if ( !out )
    {
        perror(" [E] Ошибка при открытии файла записи");
        return 4;
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
