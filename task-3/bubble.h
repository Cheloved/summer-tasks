/**
 * @file bubble.h
 * @brief Заголовочный файл для реализации пузырьковой сортировки строк.
 *
 * Содержит объявление функции `bubble_sort()`, которая выполняет пузырьковую сортировку
 * индексов строк текста, находящегося в общей памяти.
 *
 * @author Ракитин Илья Алексеевич
 */

#pragma once

#include "utils.h"

/**
 * @brief Пузырьковая сортировка массива индексов строк.
 *
 * Сортирует массив индексов строк на основе содержимого текста,
 * используя функцию linecmp() из utils.h для сравнения строк.
 *
 * @param input Указатель на начало текста (общий буфер с текстом).
 * @param array Входной массив индексов строк.
 * @param length Длина входного массива индексов.
 * @param result Выходной массив отсортированных индексов строк.
 * @return Возвращает 0 при успешном завершении.
 */
int bubble_sort(char* input, long* array, long length, long* result);
