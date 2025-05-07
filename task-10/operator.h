/**
 * @file operator.h
 * @brief Заголовочный файл работы с операторами
 *
 * Содержит объявления функций, необходимых для:
 * - проверки, является ли токен оператором
 * - получения приоритета оператора
 * - получения индекса оператора в списке
 *
 * Поддерживаются операторы: NOT, NAND, OR, XOR, NOR, IMPL, EQ, NEQ
 *
 * @author Ракитин Илья Алексеевич
 */

#pragma once

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
const s_operator OPERATORS[] = {
    { "NOT", 0 },
    { "AND", 1 },
    { "NAND", 1 },
    { "OR", 2 },
    { "XOR", 2 },
    { "NOR", 2 },
    { "IMPL", 3 },
    { "EQ", 4 },
    { "NEQ", 4 },
    { NULL, 10 }
};

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
