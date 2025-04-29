#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG 1

typedef struct
{
    uint32_t iter;
    int32_t* ar;
    int32_t left_idx;
    int32_t right_idx;
    int32_t* result;
} s_data;

void* merge_sort(void* arg)
{
    s_data* data = (s_data*)arg; // Структура входных данных

    // Длина отрезка массива для данного процесса
    int32_t length = data->right_idx - data->left_idx + 1;
    if ( length > 1 )
    {
        // Вычисление середины для дальнейшего разбиения
        int32_t mid_idx = data->left_idx + (length-1) / 2;

        if ( DEBUG )
            printf(" [debug] Iter: %d, left: %d, right: %d, mid: %d -> (%d, %d) and (%d, %d)\n", data->iter, 
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
        int32_t result_left_size = mid_idx - data->left_idx + 1;
        int32_t* result_left = (int32_t*)(malloc(sizeof(int32_t) * result_left_size));
        // Сбор остальных данных в структуру
        s_data data_left = { .iter = data->iter + 1,
                             .ar = data->ar,
                             .left_idx = data->left_idx,
                             .right_idx = mid_idx,
                             .result = result_left};

        // Аналогично для правой части
        int32_t result_right_size = data->right_idx - mid_idx + 1;
        int32_t* result_right = (int32_t*)(malloc(sizeof(int32_t) * result_right_size));
        s_data data_right = { .iter = data->iter + 1,
                             .ar = data->ar,
                             .left_idx = mid_idx + 1,
                             .right_idx = data->right_idx,
                             .result = result_right};

        // Запуск и ожидание завершения
        pthread_create(&left_thread, NULL, merge_sort, &data_left);
        pthread_create(&right_thread, NULL, merge_sort, &data_right);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        // === Соединение результатов дочерних потоков === //
        int32_t left = 0;  // Индекс в массиве результатов левой части
        int32_t right = 0; // Аналогично в провой
        int32_t i = 0;     // Индекс в текущем массиве результатов

        // Объединение массивов, пока один из них не закончится
        while ( left + data->left_idx <= mid_idx && mid_idx + 1 + right <= data->right_idx)
        {
            if ( result_left[left] < result_right[right] ) 
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
            for ( int32_t i = data->left_idx; i <= data->right_idx; i++ )
                printf("%d ", data->result[i - data->left_idx]);
            printf("\n");
        }

        // Освобождение результатов дочерних потоков из памяти
        free(result_left);
        free(result_right);
    } else {
        // Если остался только один элемент в срезе, он и устанавливается в результат
        data->result[0] = data->ar[data->left_idx];

        if ( DEBUG )
            printf(" [debug] LAST! Iter: %d, left: %d, right: %d\n", data->iter, data->left_idx, data->right_idx);
    }

    return NULL;
}

int main()
{
    int32_t array[] = { 53, 34, 42, 69, 47, 48, 59, 89, 55, 99, 2, 94, 46, 22, 98, 14, 25, 62, 71, 43 };
    int32_t length = sizeof(array) / sizeof(array[0]);

    pthread_t thread_id;
    int32_t* result = (int32_t*)(malloc(sizeof(int32_t) * length));
    s_data data = { .iter = 0,
                    .ar = array,
                    .left_idx = 0,
                    .right_idx = length - 1,
                    .result = result};
    pthread_create(&thread_id, NULL, merge_sort, &data);
    pthread_join(thread_id, NULL);

    printf("Input array: ");
    for ( int32_t i = 0; i < length; i++ )
        printf("%d ", array[i]);
    printf("\nSorted array: ");
    for ( int32_t i = 0; i < length; i++ )
        printf("%d ", result[i]);
    printf("\n");

    return 0;
}
