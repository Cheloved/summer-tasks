/**
 * @file sequence.c
 * @brief Реализация алгоритма поиска максимальной возрастающей подпоследовательности.
 *
 * Файл содержит реализацию функции `find_max_seq()`, которая находит
 * самую длинную возрастающую подпоследовательность с наибольшей суммой.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "sequence.h"

int find_max_seq(int* seq, int size, int* result, int* result_size)
{
    // Выход, если дана пустая последовательность
    if ( size == 0 )
    {
        *result_size = 0;
        return 0;
    }

    // Переменные для хранения информации
    // о максимальной последовательности
    int max_start_idx = 0;
    int max_sum = seq[0];
    int max_len = 1;

    // Переменные для хранения информации
    // о текущей последовательности
    int start_idx = 0;
    int sum = seq[0];
    int len = 1;

    // Проход по заданной последовательности
    for ( int i = 1; i < size; i++ )
    {
        // Если числа продолжают возрастать,
        // продолжить считать сумму
        if ( seq[i] > seq[i-1] ) 
        {
            // Но если в начале последовательности были
            // отрицательные числа,
            // они отсекаются, т.к. иначе входная (-1 4 8)
            // выдаст в ответ (-1 4 8), а не (4 8)
            if ( seq[i-1] < 0 )
            {
                start_idx = i;
                sum = seq[i];
                len = 1;
                continue;
            } 

            sum += seq[i];
            len++;
            continue;
        }

        // Если следующее число <= предыдущему
        // проверка на увеличение суммы или длины
        if ( (sum > max_sum) || ((sum == max_sum) && (len > max_len)) )
        {
            max_start_idx = start_idx;
            max_sum = sum;
            max_len = len;
        } 

        // Если это был последний элемент, сразу выйти
        if ( i == size )
            break;

        // Если нет, обновить счетчики
        start_idx = i;
        sum = seq[i];
        len = 1;
    }

    // Проверка последней последовательности
    if ( (sum > max_sum) || ((sum == max_sum) && (len > max_len)) )
    {
        max_start_idx = start_idx;
        max_sum = sum;
        max_len = len;
    } 

    // Запись элементов в выходной массив
    int n = 0;
    for ( int i = max_start_idx; i < max_start_idx + max_len; i++ )
        result[n++] = seq[i];

    *result_size = max_len;
    
    return 0;
}
