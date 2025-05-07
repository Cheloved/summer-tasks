/**
 * @file quick.c
 * @brief Реализация алгоритма быстрой сортировки строк.
 *
 * Файл содержит реализацию функции `quick_sort()`, которая рекурсивно
 * сортирует строки по их индексам, используя разделение на подмассивы
 * относительно опорного элемента. Для сравнения используется linecmp().
 *
 * @author Ракитин Илья Алексеевич
 */

#include "quick.h"

int quick_sort(char* input, long* array, long length, long* result)
{
    if ( array == NULL || length < 1 )
        return 0;

    if ( length == 1 )
    {
        result[0] = array[0];
        return 0;
    }

    // Определение опорного элемента
    long pivot = array[length / 2];

    // === Выделение памяти под три части массива === //
    long* left = (long*)calloc(length, sizeof(long));
    int left_length = 0;

    long* middle = (long*)calloc(length, sizeof(long));
    int middle_length = 0;

    long* right = (long*)calloc(length, sizeof(long));
    int right_length = 0;

    if ( !left || !middle || !right )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти в quick_sort()\n");
        free(left);
        free(middle);
        free(right);
        return -1;
    }

    // === Распределение массива по трем частям === //
    for ( long i = 0; i < length; i++ )
    {
        int cmp = linecmp(input, pivot, array[i]);
        if ( cmp < 0 )
            left[left_length++] = array[i];
        if ( cmp == 0 )
            middle[middle_length++] = array[i];
        if ( cmp > 0 )
            right[right_length++] = array[i];
    }

    // === Рекурсивная сортировка левой и правой частей === //
    long* left_result = (long*)malloc(sizeof(long) * left_length);
    if ( !left_result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти в quick_sort()\n");
        free(left);
        free(middle);
        free(right);
        return -1;
    }

    if ( left_length > 1 )
    {
        quick_sort(input, left, left_length, left_result);
    } else if ( left_length == 1 ) {
        left_result[0] = left[0];
    }

    long* right_result = (long*)malloc(sizeof(long) * right_length);
    if ( !right_result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти в quick_sort()\n");
        free(left_result);
        free(left);
        free(middle);
        free(right);
        return -1;
    }

    if ( right_length > 1 )
    {
        quick_sort(input, right, right_length, right_result);
    } else if ( right_length == 1 ) {
        right_result[0] = right[0];
    }

    // === Объединение массивов === //
    int current = 0;
    for ( int i = 0; i < right_length; i++ )
        result[current++] = right_result[i]; 
    for ( int i = 0; i < middle_length; i++ )
        result[current++] = middle[i]; 
    for ( int i = 0; i < left_length; i++ )
        result[current++] = left_result[i]; 

    // Освобождение памяти
    free(left);
    free(middle);
    free(right);
    free(left_result);
    free(right_result);

    return 0;
}
