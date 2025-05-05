#include "parser.h"

char* OPERATORS[] = { "NOT", "AND", "OR", NULL };

int is_operator(char* token)
{
    char** ptr = OPERATORS;
    while ( *ptr )
        if ( !strcmp(token, *(ptr++)) )
            return 1;

    return 0;
}

int get_priority(char* operator)
{
    char** ptr = OPERATORS;
    int i = 0;
    while ( *ptr )
    {
        if ( !strcmp(operator, *(ptr++)) )
            return i;
        i++;
    }

    return -1;
}

int to_postfix(char** tokens, int size, char** postfix)
{
    s_stack stack = { init_char_arr(size, MAX_TOKEN_LEN), -1, MAX_TOKENS };

    char** queue = init_char_arr(size, MAX_TOKEN_LEN); 
    int queue_top = -1;
    char buffer[MAX_TOKEN_LEN];

    for ( int i = 0; i < size; i++ )
    {
        printf("[debug] token: %s\n", tokens[i]);
        printf("[debug] stack: ");
        for ( int si = 0; si <= stack.top; si++ )
            printf("%s ", stack.elems[si]);
        printf("\n");

        printf("[debug] queue: ");
        for ( int qi = 0; qi <= queue_top; qi++ )
            printf("%s ", queue[qi]);
        printf("\n\n");


        // Если токен - переменная, добавить в очередь
        if ( !is_operator(tokens[i]) &&
             strcmp(tokens[i], "(") &&
             strcmp(tokens[i], ")") )
        {
            strcpy(queue[++queue_top], tokens[i]);
            continue;
        }

        // Если токен - оператор
        if ( is_operator(tokens[i]) ) 
        {
            // Если стек пустой или в вершине стека левая скобка,
            // добавить токен в стек
            if ( is_empty(stack) )
            {
                push(&stack, tokens[i]);
                continue;
            }

            peek(stack, buffer);
            if ( !strcmp(buffer, "(") )
            {
                push(&stack, tokens[i]);
                continue;
            }

            // Если в вершине стека оператор с более высоким приоритетом,
            // добавить в стек
            int priority = get_priority(tokens[i]);

            peek(stack, buffer);
            int top_priority = get_priority(buffer);

            if ( priority < top_priority )
            {
                push(&stack, tokens[i]);
                continue;
            }

            // Если нет, выгрузить из стека всё в очередь
            // до появления левой скобки или оператора 
            // c большим приоритетом
            while ( !is_empty(stack) )
            {
                if ( !strcmp(buffer, "(") )
                    break;

                top_priority = get_priority(buffer);
                if ( priority < top_priority )
                    break;

                pop(&stack, queue[++queue_top]);
                peek(stack, buffer);
            }

            // После этого добавить токен в стек
            push(&stack, tokens[i]);
        }

        // Если токен - левая скобка, добавить ее в стек
        if ( !strcmp(tokens[i], "(") )
        {
            push(&stack, tokens[i]);
            continue;
        }

        // Если правая - выгружать из стека в очередь всё,
        // пока не дойдет до левой
        if ( !strcmp(tokens[i], ")") )
        {
            char el[MAX_TOKEN_LEN];
            pop(&stack, el);

            while ( strcmp(el, "(") )
            {
                strcpy(queue[++queue_top], el);
                memset(el, 0, MAX_TOKEN_LEN);
                pop(&stack, el);
            }
            // stack.top--;
        }
    }

    // В конце выражения выгружаем весь стек в очередь
    while ( !is_empty(stack) )
        pop(&stack, queue[++queue_top]);

    // Сохранение очереди в результат
    for ( int i = 0; i < queue_top+1; i++ )
        strcpy(postfix[i], queue[i]);

    return 0;
}
