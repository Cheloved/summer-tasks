/**
 * @file parser.h
 * @brief Заголовочный файл для парсинга и вычисления логических выражений.
 *
 * Содержит объявления функций, необходимых для:
 * - преобразования инфиксного выражения в постфиксное (обратная польская запись),
 * - вычисления значения выражения.
 *
 * Поддерживаются операторы: NOT, NAND, OR, XOR, NOR, IMPL, EQ, NEQ
 *
 * @author Ракитин Илья Алексеевич
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "dynamic.h"
#include "stack.h"
#include "operator.h"
#include "variable.h"

/**
 * @brief Преобразует инфиксное выражение в постфиксное (обратная польская запись).
 *
 * Используется алгоритм Дейкстры (Shunting Yard).
 *
 * @param tokens Массив входных токенов.
 * @param size Количество входных токенов.
 * @param postfix Выходной массив для хранения постфиксного выражения.
 * @return Возвращает 0 при успешном завершении.
 */
int to_postfix(char** tokens, int size, char** postfix);

/**
 * @brief Вычисляет значение постфиксного выражения.
 *
 * @param tokens Массив токенов в постфиксной форме.
 * @param size Количество токенов.
 * @return Возвращает результат вычисления выражения.
 */
int evaluate(char** tokens, int size);
