/**
 * @file main.c
 * @brief Точка входа программы для анализа числовой последовательности.
 *
 * Программа:
 * - принимает путь к файлу и количество элементов,
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
 * Принимает два аргумента командной строки:
 * - путь к файлу с числовой последовательностью,
 * - количество элементов для чтения.
 *
 * Считывает последовательность из файла, обрабатывает её и выводит
 * найденную максимальную возрастающую подпоследовательность с наибольшей суммой.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает 0 при успешном завершении, отрицательное число в случае ошибки.
 */
int main(int argc, char** argv)
{
    if ( argc != 3 )
    {
        fprintf(stderr, " [E] Должно быть 2 аргумента: путь к файлу и кол-во элементов\n");
        return 1;
    }

    int size = atoi(argv[2]);
    if ( size <= 0 )
    {
        fprintf(stderr, " [E] Неверный размер\n");
        return 2;
    }

    int* seq = (int*)calloc(size, sizeof(int));
    if ( !seq )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для seq\n");
        return 3;
    }

    if ( !read_seq(argv[1], seq, size) )
    {
        for ( int i = 0; i < size; i++ )
            printf("%d ", seq[i]);
    } else {
        fprintf(stderr, " [E] Ошибка чтения последовательности\n");
        free(seq);
        return 4;
    }
    printf("\n");

    int result_size = 0;
    int* result = (int*)calloc(size, sizeof(int));
    if ( !result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для seq\n");
        free(seq);
        return 5;
    }
    find_max_seq(seq, size, result, &result_size);
    
    printf("Максимальная последовательность: ");
    for ( int i = 0; i < result_size; i++ )
        printf("%d ", result[i]);

    free(seq);
    free(result);

    return 0;
}
