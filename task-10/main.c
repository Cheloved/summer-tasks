/**
 * @file main.c
 * @brief Точка входа программы, реализующей парсер и вычислитель логических выражений.
 *
 * Программа:
 * - принимает строку с логическим выражением,
 * - разбивает её на токены,
 * - преобразует в постфиксную запись (обратная польская),
 * - запрашивает значения переменных,
 * - вычисляет результат выражения.
 *
 * Поддерживаемые операторы: `NOT`, `AND`, `OR`.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "dynamic.h"
#include "parser.h"

/**
 * @brief Точка входа программы.
 *
 * Обрабатывает заданное логическое выражение, выводит токены,
 * постфиксную форму выражения и результат его вычисления.
 *
 * @return Возвращает 0 при успешном завершении.
 */
int main()
{
    const char* expr = "(A AND B) OR (C AND NOT D)";
    // const char* expr = "A AND B OR C ";
    // const char* expr = "A OR B AND C ";

    // Выделение памяти и заполнение массива токенов
    char** tokens = init_char_arr(MAX_TOKENS, MAX_TOKEN_LEN);
    int tokens_len = tokenize(expr, tokens);

    printf("Кол-во токенов: %d\nТокены: ", tokens_len);
    for ( int i = 0; i < tokens_len; i++ )
        printf("\"%s\" ", tokens[i]);
    printf("\n");

    // Конвертирование в постфиксную нотацию
    char** postfix = init_char_arr(tokens_len, MAX_TOKEN_LEN);
    to_postfix(tokens, tokens_len, postfix);

    printf("В постфиксной нотации: ");
    for ( int i = 0; i < tokens_len; i++ )
        printf("%s ", postfix[i]);
    printf("\n");

    // Вычисление результата
    int result = evaluate(postfix, tokens_len);
    printf("Результат вычисления: %d\n", result);

    return 0;
}
