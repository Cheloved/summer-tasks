#include "merge.h"

void merge_arrays(int* result, int* l, int lsize, int* r, int rsize)
{
    int left = 0;  // Индекс в массиве результатов левой части
    int right = 0; // Аналогично в провой
    int i = 0;     // Индекс в текущем массиве результатов

    // Объединение массивов с сортировкой,
    // пока один из них не закончится
    while ( left < lsize && right < rsize - 1 )
    {
        if ( l[left] < r[right] ) 
            result[i++] = l[left++];
        else
            result[i++] = r[right++];
    }

    // Добавление остаточной части
    while ( left < lsize )
        result[i++] = l[left++];

    while ( right < rsize - 1 )
        result[i++] = r[right++];
}

void* merge_sort_thread(void* arg)
{
    s_data* data = (s_data*)arg;

    // Длина отрезка массива для данного процесса
    int length = data->right_idx - data->left_idx + 1;

    // Если остался только один элемент в срезе, он и устанавливается в результат
    if ( length <= 1 )
    {
        data->result[0] = data->ar[data->left_idx];
        return NULL;
    }

    // Вычисление середины для дальнейшего разбиения
    int mid_idx = data->left_idx + (length-1) / 2;

    // Запуск новых потоков для левой и правой частей.
    // Один из них будет от текущего левого края до середины,
    // а другой от середины+1 до правого края
    pthread_t left_thread, right_thread;
    
    // Выделение памяти для результата дочернего левого потока
    int result_left_size = mid_idx - data->left_idx + 1;
    int* result_left = (int*)(malloc(sizeof(int) * result_left_size));
    if ( !result_left )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти!\n");
        return NULL;
    }

    // Сбор остальных данных в структуру
    s_data data_left = { .iter = data->iter + 1,
                         .ar = data->ar,
                         .left_idx = data->left_idx,
                         .right_idx = mid_idx,
                         .result = result_left};

    // Аналогично для правой части
    int result_right_size = data->right_idx - mid_idx + 1;
    int* result_right = (int*)(malloc(sizeof(int) * result_right_size));
    if ( !result_right )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти!\n");
        free(result_left);
        return NULL;
    }
    s_data data_right = { .iter = data->iter + 1,
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
    merge_arrays(data->result, result_left, result_left_size, result_right, result_right_size);

    // Освобождение результатов дочерних потоков из памяти
    free(result_left);
    free(result_right);

    return NULL;
}

int merge_sort(int* array, int length, int* result)
{
    // Первоначальное указание индексов
    pthread_t thread_id;
    s_data data = { .iter = 0,
                    .ar = array,
                    .left_idx = 0,
                    .right_idx = length - 1,
                    .result = result};

    // Запуск потока и ожидание завершения
    pthread_create(&thread_id, NULL, merge_sort_thread, &data);
    pthread_join(thread_id, NULL);

    return 0;
}
