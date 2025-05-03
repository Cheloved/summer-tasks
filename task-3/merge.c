#include "merge.h"

void* merge_sort_thread(void* arg)
{
    s_data* data = (s_data*)arg; // Структура входных данных

    // Длина отрезка массива для данного процесса
    long length = data->right_idx - data->left_idx + 1;
    if ( length > 1 )
    {
        // Вычисление середины для дальнейшего разбиения
        long mid_idx = data->left_idx + (length-1) / 2;

        if ( DEBUG )
            printf(" [debug] Iter: %d, left: %ld, right: %ld, mid: %ld -> (%ld, %ld) and (%ld, %ld)\n", data->iter, 
                    data->left_idx,
                    data->right_idx,
                    mid_idx,
                    data->left_idx,
                    mid_idx,
                    mid_idx + 1,
                    data->right_idx);

        // Запуск новых потоков для левой и правой частей
        // Один из них будет от текущего левого края до середины,
        // а другой от середины+1 до правого края
        pthread_t left_thread, right_thread;
        
        // Выделение памяти для результата дочернего левого потока
        long result_left_size = mid_idx - data->left_idx + 1;
        long* result_left = (long*)(malloc(sizeof(long) * result_left_size));
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

        // === Соединение результатов дочерних потоков === //
        long left = 0;  // Индекс в массиве результатов левой части
        long right = 0; // Аналогично в провой
        long i = 0;     // Индекс в текущем массиве результатов

        // Объединение массивов, пока один из них не закончится
        while ( left + data->left_idx <= mid_idx && mid_idx + 1 + right <= data->right_idx)
        {
            // if ( result_left[left] < result_right[right] ) 
            // Сравнение строк вместо чисел //
            if ( linecmp(data->input, result_left[left], result_right[right]) <= 0 ) 
                data->result[i++] = result_left[left++];
            else
                data->result[i++] = result_right[right++];
        }

        // Добавление остаточной части
        while ( left + data->left_idx <= mid_idx )
            data->result[i++] = result_left[left++];

        while ( mid_idx + 1 + right <= data->right_idx )
            data->result[i++] = result_right[right++];

        if ( DEBUG )
        {
            printf(" [debug] Iter: %d, result: ", data->iter);
            for ( long i = data->left_idx; i <= data->right_idx; i++ )
                printf("%ld ", data->result[i - data->left_idx]);
            printf("\n");
        }

        // Освобождение результатов дочерних потоков из памяти
        free(result_left);
        free(result_right);
    } else {
        // Если остался только один элемент в срезе, он и устанавливается в результат
        data->result[0] = data->ar[data->left_idx];

        if ( DEBUG )
            printf(" [debug] LAST! Iter: %d, left: %ld, right: %ld\n", data->iter, data->left_idx, data->right_idx);
    }

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
