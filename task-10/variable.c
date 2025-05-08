/**
 * @file variable.c
 * @brief Реализация функций для работы с введенными переменными
 *
 * @author Ракитин Илья Алексеевич
 */

#include "variable.h"

s_variable* init_vars_arr(int size)
{
    s_variable* vars = (s_variable*)calloc(size, sizeof(s_variable));
    if ( !vars )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти для переменных\n");
        return NULL;
    }

    for ( int i = 0; i < size; i++ )
    {
        vars[i].name = (char*)calloc(MAX_TOKEN_LEN, sizeof(char));
        if ( !vars[i].name )
        {
            fprintf(stderr, " [E] Ошибка при выделении памяти для переменных\n");
            free_vars_arr(vars, size);
            return NULL;
        }
    }
    
    return vars;
}

void free_vars_arr(s_variable* vars, int size)
{
    for ( int i = 0; i < size; i++ )
        free(vars[i].name);

    free(vars);
}

int get_value(char* token)
{
    char buffer[MAX_TOKEN_LEN];
    int number;

    printf(" > Введите значения для %s: ", token);

    while ( 1 )
    {
        // Считывает строку и пытается преобразовать её в число.
        // Повторяет, пока пользователь не введет корректное число
        if ( fgets(buffer, MAX_TOKEN_LEN, stdin) != NULL )
        {
            if ( sscanf(buffer, "%d", &number) == 1 )
            {
                if ( number == 0 || number == 1 )
                    return number;
                else
                    fprintf(stderr, " [E] Неверный ввод. Для переменных допустимы только значения 0 и 1\n");
            } else {
                fprintf(stderr, " [E] Неверный ввод. Попробуйте еще раз\n");
            }
        } else {
            fprintf(stderr, " [E] Ошибка при чтении\n");
        }
    }

    return -1;
}

int find_var(s_variable* vars, int n_vars, char* token)
{
    for ( int i = 0; i < n_vars; i++ )
        if ( !strcmp(token, vars[i].name) )
            return i;

    return -1;
}
