/**
 * @file sorting.h
 * @brief Общие функции для работы с текстовыми файлами и управления сортировкой строк.
 *
 * Содержит объявления функций, необходимых для чтения файла, подсчёта строк,
 * получения индексов строк, выбора метода сортировки и сохранения результата.
 *
 * @author Ракитин Илья Алексеевич
 */

#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bubble.h"
#include "merge.h"
#include "quick.h"
#include "utils.h"

/**
 * @brief Получает размер файла по указанному пути.
 *
 * Открывает файл в бинарном режиме и определяет его размер.
 *
 * @param path Путь к файлу.
 * @return Размер файла в байтах или -1 при ошибке.
 */
long get_file_size(char* path);

/**
 * @brief Считывает содержимое файла в указанный буфер.
 *
 * @param path Путь к файлу.
 * @param size Размер данных, которые нужно считать.
 * @param result Указатель на буфер для хранения содержимого файла.
 * @return Возвращает 0 при успешном завершении, -1 при ошибке.
 */
int read_file(char* path, long size, char* result);

/**
 * @brief Определяет количество непустых строк в тексте.
 *
 * Непустой строкой считаются любые символы кроме пробелов до перевода строки.
 *
 * @param input Указатель на начало текста.
 * @param size Размер текста в байтах.
 * @return Количество непустых строк.
 */
int get_lines_count(char* input, long size);

/**
 * @brief Заполняет массив индексов начала непустых строк.
 *
 * @param input Указатель на начало текста.
 * @param size Размер текста в байтах.
 * @param result Выходной массив индексов строк.
 * @return Возвращает 0 при успешном завершении.
 */
int get_indexes(char* input, long size, long* result);

/**
 * @brief Проверяет, поддерживается ли указанный метод сортировки.
 *
 * Доступные методы: "bubble", "merge", "quick".
 *
 * @param method Имя метода сортировки.
 * @return Возвращает 1, если метод поддерживается, иначе — 0.
 */
int method_available(char* method);

/**
 * @brief Сортирует строки из входного файла заданным методом и сохраняет результат в выходной файл.
 *
 * @param input Путь к входному файлу.
 * @param output Путь к выходному файлу.
 * @param method Метод сортировки ("bubble", "merge", "quick").
 * @return Возвращает 0 при успешном завершении, -1 при ошибке.
 */
int sort_file(char* input, char* output, char* method);

/**
 * @brief Сохраняет содержимое буфера в файл.
 *
 * @param path Путь к файлу для записи.
 * @param buffer Буфер с данными для записи.
 * @return Возвращает 0 при успешном завершении, -1 при ошибке.
 */
int save(char* path, char* buffer);
