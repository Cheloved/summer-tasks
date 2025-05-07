/**
 * @file main.c
 * @brief Точка входа программы для анализа числовой последовательности.
 *
 * Программа:
 * - принимает путь к файлу,
 * - считывает последовательность из файла,
 * - находит самую длинную возрастающую подпоследовательность с наибольшей суммой,
 * - выводит результат на экран.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "sequence.h"

/**
 * @brief Точка входа программы.
 *
 * Принимает аргумент командной строки:
 * - путь к файлу с числовой последовательностью.
 *
 * Считывает последовательность из файла, обрабатывает её и выводит
 * найденную максимальную возрастающую подпоследовательность с наибольшей суммой.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает 0 при успешном завершении, другое число в случае ошибки.
 */
int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, " [E] Должен быть 1 аргумент: путь к файлу\n");
        return 1;
    }

    int size = get_seq_len(argv[1]);

    int* seq = (int*)calloc(size, sizeof(int));
    if ( !seq )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для seq\n");
        return 2;
    }

    if ( !read_seq(argv[1], seq, size) )
    {
        for ( int i = 0; i < size; i++ )
            printf("%d ", seq[i]);
    } else {
        fprintf(stderr, " [E] Ошибка чтения последовательности\n");
        free(seq);
        return 3;
    }
    printf("\n");

    int result_size = 0;
    int* result = (int*)calloc(size, sizeof(int));
    if ( !result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для seq\n");
        free(seq);
        return 4;
    }
    find_max_seq(seq, size, result, &result_size);
    
    printf("Максимальная последовательность: ");
    for ( int i = 0; i < result_size; i++ )
        printf("%d ", result[i]);

    free(seq);
    free(result);

    return 0;
}
