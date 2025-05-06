/**
 * @file bubble.c
 * @brief Реализация алгоритма пузырьковой сортировки строк.
 *
 * Файл содержит реализацию функции `bubble_sort()`, которая реализует
 * пузырьковый метод сортировки строк по их индексам. Используется для
 * сортировки строк текстового файла без изменения оригинального порядка в памяти.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "bubble.h"

int bubble_sort(char* input, long* array, long length, long* result)
{
    // Копирование исходного массива
    for ( int i = 0; i < length; i++ )
        result[i] = array[i];

    // Сортировка пузырьком, где вместо сравнения
    // чисел применяется сравнение linecmp()
    for ( int i = 0; i < length; i++ )
    {
        for ( int j = 0; j < length - i - 1; j++ )
        {
            if ( linecmp(input, result[j], result[j+1]) >= 0 ) 
            {
                int buf = result[j];
                result[j] = result[j+1];
                result[j+1] = buf;
            }
        }
    }

    return 0;
}
