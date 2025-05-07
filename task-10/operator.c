/**
 * @file operator.c
 * @brief Реализация функций для работы с операторами
 *
 * @author Ракитин Илья Алексеевич
 */

#include "operator.c"

int is_operator(char* token)
{
    int i = 0;
    while ( OPERATORS[i].name )
        if ( !strcmp(token, OPERATORS[i++].name) )
            return 1;

    return 0;
}

int get_priority(char* operator)
{
    int i = 0;
    while ( OPERATORS[i].name )
    {
        if ( !strcmp(operator, OPERATORS[i].name) )
            return OPERATORS[i].priority;
        i++;
    }

    return -1;
}

int get_oper_index(char* operator)
{
    int i = 0;
    while ( OPERATORS[i].name )
    {
        if ( !strcmp(operator, OPERATORS[i].name) )
            return i;
        i++;
    }

    return -1;
}
