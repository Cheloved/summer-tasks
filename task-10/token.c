/**
 * @file token.c
 * @brief Реализация функции лексического анализа строки.
 *
 * Содержит реализацию функции `tokenize()`, которая разбивает строку на отдельные токены,
 * используя разделители — пробелы и скобки.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "token.h"

int tokenize(char* input, char** output)
{
    int current_token_idx = 0;  // Индекс в массиве output
    char* start_ptr = input;    // Указатель начала текущего токена
    char* ptr = input;          // Указатель на текущий символ
    int tokens_found = 0;       // Кол-во найденных токенов
    int last_bracket = 0;

    // Проход по строке
    while ( *ptr )
    {
        // Если текущий символ - скобка, добавляется
        // последние недобавленные символы до нее и сама скобка
        if ( *ptr == '(' || *ptr == ')' )
        {
            // Добавление только если содержатся символы
            if ( ptr - start_ptr != 0 )
            {
                strncpy(output[current_token_idx++], start_ptr, ptr-start_ptr);
                tokens_found++;
            }

            // Добавление скобки
            output[current_token_idx++][0] = *ptr;
            tokens_found++;

            last_bracket = 1;
            start_ptr = ptr + 1;
        }

        // Аналогично с пробелом, только без его добавления
        if ( *ptr == ' ' )
        {
            if ( ptr - start_ptr != 0 )
            {
                strncpy(output[current_token_idx++], start_ptr, ptr-start_ptr);
                tokens_found++;
            }

            last_bracket = 0;
            start_ptr = ptr + 1;
        }

        ptr++;
    }

    // Обработка последнего токена
    if ( !last_bracket )
    {
        strncpy(output[current_token_idx++], start_ptr, ptr-start_ptr);
        tokens_found++;
    }

    return tokens_found;
}
