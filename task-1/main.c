#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

typedef struct
{
    uint32_t iter;
    int32_t* ar;
    int32_t left_idx;
    int32_t right_idx;
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
        s_data data_left = { .iter = data->iter + 1,
                             .ar = data->ar,
                             .left_idx = data->left_idx,
                             .right_idx = mid_idx};

        s_data data_right = { .iter = data->iter + 1,
                             .ar = data->ar,
                             .left_idx = mid_idx + 1,
                             .right_idx = data->right_idx};

        // Запуск и ожидание завершения
        pthread_create(&left_thread, NULL, merge_sort, &data_left);
        pthread_create(&right_thread, NULL, merge_sort, &data_right);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }


    return NULL;
}

int main()
{
    int32_t array[] = { 53, 34, 42, 69, 47, 48, 59, 89, 55, 99, 2, 94, 46, 22, 98, 14, 25, 62, 71, 43 };
    uint32_t length = 20;

    pthread_t thread_id;
    s_data data = { .iter = 0,
                    .ar = array,
                    .left_idx = 0,
                    .right_idx = length - 1};
    pthread_create(&thread_id, NULL, merge_sort, &data);
    pthread_join(thread_id, NULL);

    return 0;
}
