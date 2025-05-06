/**
 * @file parser.h
 * @brief Заголовочный файл для парсинга и вычисления логических выражений.
 *
 * Содержит объявления функций, необходимых для:
 * - проверки является ли строка оператором,
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

/**
 * @struct s_operator 
 * @brief Содержит информацию о операторе
 */
typedef struct
{
    char* name;
    int priority;
} s_operator;

/**
 * @var OPERATORS
 * @brief Массив структур поддерживаемых операторов
 */
extern s_operator OPERATORS[];

/**
 * @enum ENUM_OPERATORS 
 * @brief Содержит информацию о операторе
 */
enum ENUM_OPERATORS { NOT, AND, NAND, OR, XOR, NOR, IMPL, EQ, NEQ };

/**
 * @brief Проверяет, является ли строка допустимым оператором.
 *
 * @param token Входной токен.
 * @return Возвращает 1, если токен — оператор, иначе — 0.
 */
int is_operator(char* token);

/**
 * @brief Получает приоритет оператора.
 *
 * 0 - самый высокий приоритет. Чем число больше, тем приоритет меньше
 *
 * @param token Входной токен.
 * @return Приоритет оператора
 */
int get_priority(char* operator);

/**
 * @brief Получает индекс оператора в списке
 *
 * @param token Входной токен.
 * @return Индекс оператора
 */
int get_oper_index(char* operator);

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
 * @brief Получает числовое значение для переменной.
 *
 * Если переменная неизвестна, запрашивает у пользователя.
 *
 * @param token Токен (имя переменной или число).
 * @return Возвращает целочисленное значение для токена.
 */
int get_value(char* token);

/**
 * @brief Вычисляет значение постфиксного выражения.
 *
 * @param tokens Массив токенов в постфиксной форме.
 * @param size Количество токенов.
 * @return Возвращает результат вычисления выражения.
 */
int evaluate(char** tokens, int size);
