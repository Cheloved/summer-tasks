/**
 * @file stack.c
 * @brief Реализация стека строк.
 *
 * Файл содержит реализацию базовых операций над стеком строк:
 * - проверка на пустоту и заполненность,
 * - добавление элемента (push),
 * - извлечение элемента (pop),
 * - просмотр верхнего элемента (peek).
 *
 * @author Ракитин Илья Алексеевич
 */

#include "stack.h"

int is_empty(s_stack stack)
{
    return stack.top == -1;
}

int is_full(s_stack stack)
{
    return stack.top == stack.max_num - 1;
}

int push(s_stack* stack, char* value)
{
    if ( is_full(*stack) )
    {
        fprintf(stderr, " [E] Переполнение стека\n");
        return -1;
    }

    strcpy(stack->elems[++stack->top], value);
    return 0;
}

int pop(s_stack* stack, char* result)
{
    if ( is_empty(*stack) )
    {
        fprintf(stderr, " [E] Стек пустой, невозможно извлечь элемент в pop()\n");
        return -1;
    }

    strcpy(result, stack->elems[stack->top--]);
    return 0;
}

int peek(s_stack stack, char* result)
{
    if ( is_empty(stack) )
    {
        fprintf(stderr, " [E] Стек пустой, невозможно извлечь элемент в peek()\n");
        return -1;
    }

    strcpy(result, stack.elems[stack.top]);
    return 0;
}
