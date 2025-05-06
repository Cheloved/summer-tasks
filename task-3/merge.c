/**
 * @file merge.c
 * @brief Реализация параллельной сортировки слиянием с использованием потоков.
 *
 * Реализует функцию `merge_sort()`, которая запускает сортировку в отдельном потоке.
 * Каждый рекурсивный шаг делится между потоками. После окончания сортировки
 * частичные результаты объединяются.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "merge.h"

void merge_arrays(s_data* data, long* l, int lsize, long* r, int rsize)
{
    int32_t left = 0;  // Индекс в массиве результатов левой части
    int32_t right = 0; // Аналогично в провой
    int32_t i = 0;     // Индекс в текущем массиве результатов

    // Объединение массивов с сортировкой,
    // пока один из них не закончится
    while ( left < lsize && right < rsize - 1 )
    {
        if ( linecmp(data->input, l[left], r[right]) <= 0 ) 
            data->result[i++] = l[left++];
        else
            data->result[i++] = r[right++];
    }

    // Добавление остаточной части
    while ( left < lsize )
        data->result[i++] = l[left++];

    while ( right < rsize - 1 )
        data->result[i++] = r[right++];
}

void* merge_sort_thread(void* arg)
{
    s_data* data = (s_data*)arg; // Структура входных данных

    // Длина отрезка массива для данного процесса
    long length = data->right_idx - data->left_idx + 1;

    if ( length == 0 )
        return NULL;

    // Если остался только один элемент в срезе, 
    // он и устанавливается в результат
    if ( length == 1 )
    {
        data->result[0] = data->ar[data->left_idx];
        return NULL;
    }

    // Вычисление середины для дальнейшего разбиения
    long mid_idx = data->left_idx + (length-1) / 2;

    // Запуск новых потоков для левой и правой частей
    // Один из них будет от текущего левого края до середины,
    // а другой от середины+1 до правого края
    pthread_t left_thread, right_thread;
    
    // Выделение памяти для результата дочернего левого потока
    long result_left_size = mid_idx - data->left_idx + 1;
    long* result_left = (long*)(malloc(sizeof(long) * result_left_size));
    if ( !result_left )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти!\n");
        return NULL;
    }

    // Сбор остальных данных в структуру
    s_data data_left = { .iter = data->iter + 1,
                         .input = data->input,
                         .ar = data->ar,
                         .left_idx = data->left_idx,
                         .right_idx = mid_idx,
                         .result = result_left};

    // Аналогично для правой части
    long result_right_size = data->right_idx - mid_idx + 1;
    long* result_right = (long*)(malloc(sizeof(long) * result_right_size));
    if ( !result_right )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти!\n");
        free(result_left);
        return NULL;
    }

    s_data data_right = { .iter = data->iter + 1,
                         .input = data->input,
                         .ar = data->ar,
                         .left_idx = mid_idx + 1,
                         .right_idx = data->right_idx,
                         .result = result_right};

    // Запуск и ожидание завершения
    pthread_create(&left_thread, NULL, merge_sort_thread, &data_left);
    pthread_create(&right_thread, NULL, merge_sort_thread, &data_right);
    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    // Соединение результатов дочерних потоков
    merge_arrays(data, result_left, result_left_size, result_right, result_right_size); 

    // Освобождение результатов дочерних потоков из памяти
    free(result_left);
    free(result_right);

    return NULL;
}

int merge_sort(char* input, long* array, long length, long* result)
{
    // Первоначальное указание индексов и запуск потока
    pthread_t thread_id;
    s_data data = { .iter = 0,
                    .input = input,
                    .ar = array,
                    .left_idx = 0,
                    .right_idx = length - 1,
                    .result = result};

    pthread_create(&thread_id, NULL, merge_sort_thread, &data);
    pthread_join(thread_id, NULL);

    return 0;
}
