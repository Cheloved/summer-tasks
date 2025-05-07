/**
 * @file merge.h
 * @brief Заголовочный файл реализации параллельной сортировки слиянием.
 *
 * Содержит объявление структуры данных для передачи параметров в поток,
 * объявления функций для запуска сортировки
 *
 * @author Ракитин Илья Алексеевич
 */

#pragma once

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
    uint iter;     // Текущая глубина разделения (для отладки)
    int* ar;       // Указатель на исходный массив
    int left_idx;  // Индекс начала среза для текущего потока
    int right_idx; // Индекс конца среза
    int* result;   // Массив, куда будет сохранен результат слияния
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
void merge_arrays(int* result, int* l, int lsize, int* r, int rsize);

/**
 * @brief сортировка, выполняемая отдельными потоками
 *
 * @param arg структура входных данных, содержит указатель на s_data
 */
void* merge_sort_thread(void* arg);

/**
 * @brief сортировка массива параллельным Merge Sort
 *
 * @param array массив, который нужно отсортировать
 * @param length длина массива array
 * @param result массив, в который будет сохранен результат
 */
int merge_sort(int* array, int length, int* result);
