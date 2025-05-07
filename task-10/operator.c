/**
 * @file operator.c
 * @brief Реализация функций для работы с операторами
 *
 * @author Ракитин Илья Алексеевич
 */

#include "operator.h"

s_operator OPERATORS[] = {
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
