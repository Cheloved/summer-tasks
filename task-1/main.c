/**
 * @file main.c
 * @brief Реализация многопоточной сортировки слиянием (Parallel Merge Sort)
 *
 * В данном файле реализована многопоточная версия алгоритма сортировки слиянием,
 * позволяющая использовать несколько потоков для ускорения процесса сортировки.
 * Алгоритм сохраняет временную сложность O(n log n) и использует библиотеку pthreads
 * для распараллеливания задач на этапах разделения массива.
 *
 * @author Ракитин Илья Алексеевич
 * @date 29.04.2025
 *
 * @details
 * Реализация использует стандартную библиотеку <pthread.h> для создания
 * параллельных потоков. Merge-операция остаётся последовательной из-за
 * необходимости сохранить стабильность сортировки.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include "merge.h"
#include "io.h"

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, " [E] Необходимо передать путь к файлу с массивом в качестве аргумента\n");
        return 1;
    }

    int size = get_seq_len(argv[1]);
    if ( size < 0 )
    {
        fprintf(stderr, " [E] Ошибка получения длины\n");
        return 2;
    }
    int* array = (int*)calloc(size, sizeof(int));
    if ( !array )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для массива\n");
        return 3;
    }

    if ( !read_seq(argv[1], array, size) )
    {
        for ( int i = 0; i < size; i++ )
            printf("%d ", array[i]);
    } else {
        fprintf(stderr, " [E] Ошибка чтения массива\n");
        free(array);
        return 4;
    }
    printf("\n");

    int* result = (int*)(malloc(sizeof(int) * size));

    merge_sort(array, size, result);

    printf("Input array: ");
    for ( int32_t i = 0; i < size; i++ )
        printf("%d ", array[i]);

    printf("\nSorted array: ");
    for ( int32_t i = 0; i < size; i++ )
        printf("%d ", result[i]);
    printf("\n");

    free(result);
    return 0;
}
