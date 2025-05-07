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
#include <unistd.h>

/**
 * @struct s_data
 * @brief структура для передачи данных в качестве аргумента в другой поток
 */
typedef struct
{
    uint32_t iter;     // Текущая глубина разделения (для отладки)
    int32_t* ar;       // Указатель на исходный массив
    int32_t left_idx;  // Индекс начала среза для текущего потока
    int32_t right_idx; // Индекс конца среза
    int32_t* result;   // Массив, куда будет сохранен результат слияния
} s_data;

/**
 * @brief объединяет массивы l и r в result
 *
 * @param result Динамический массив чисел, куда будет сохранен результат
 * @param l Динамический массив результата левого дочернего потока
 * @param lsize Кол-во элементов в массиве l
 * @param r Аналогично l для правой части
 * @param rsize Аналогично lsize для правой части
 */
void merge_arrays(int32_t* result, int32_t* l, int lsize, int32_t* r, int rsize)
{
    int32_t left = 0;  // Индекс в массиве результатов левой части
    int32_t right = 0; // Аналогично в провой
    int32_t i = 0;     // Индекс в текущем массиве результатов

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

/**
 * @brief сортировка, выполняемая отдельными потоками
 *
 * @param arg структура входных данных, содержит указатель на s_data
 */
void* merge_sort_thread(void* arg)
{
    s_data* data = (s_data*)arg;

    // Длина отрезка массива для данного процесса
    int32_t length = data->right_idx - data->left_idx + 1;

    // Если остался только один элемент в срезе, он и устанавливается в результат
    if ( length <= 1 )
    {
        data->result[0] = data->ar[data->left_idx];
        return NULL;
    }

    // Вычисление середины для дальнейшего разбиения
    int32_t mid_idx = data->left_idx + (length-1) / 2;

    // Запуск новых потоков для левой и правой частей.
    // Один из них будет от текущего левого края до середины,
    // а другой от середины+1 до правого края
    pthread_t left_thread, right_thread;
    
    // Выделение памяти для результата дочернего левого потока
    int32_t result_left_size = mid_idx - data->left_idx + 1;
    int32_t* result_left = (int32_t*)(malloc(sizeof(int32_t) * result_left_size));
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
    int32_t result_right_size = data->right_idx - mid_idx + 1;
    int32_t* result_right = (int32_t*)(malloc(sizeof(int32_t) * result_right_size));
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

/**
 * @brief сортировка массива параллельным Merge Sort
 *
 * @param array массив, который нужно отсортировать
 * @param length длина массива array
 * @param result массив, в который будет сохранен результат
 */
int merge_sort(int32_t* array, uint32_t length, int32_t* result)
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

int main()
{
    // int32_t array[] = { 1 };
    // int32_t array[] = { 2, 2, 2, 2, 2 };
    int32_t array[] = { 53, 34, 42, 69, 47, 48, 59, 89, 55, 99, 2, 94, 46, 22, 98, 14, 25, 62, 71, 43 };
    int32_t length = sizeof(array) / sizeof(array[0]);
    int32_t* result = (int32_t*)(malloc(sizeof(int32_t) * length));

    merge_sort(array, length, result);

    printf("Input array: ");
    for ( int32_t i = 0; i < length; i++ )
        printf("%d ", array[i]);

    printf("\nSorted array: ");
    for ( int32_t i = 0; i < length; i++ )
        printf("%d ", result[i]);
    printf("\n");

    free(result);
    return 0;
}
