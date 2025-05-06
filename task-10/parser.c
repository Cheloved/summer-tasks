/**
 * @file parser.c
 * @brief Реализация парсера логических выражений.
 *
 * Файл содержит реализацию следующих этапов обработки выражения:
 * 1. Разбор на токены (лексический анализ),
 * 2. Преобразование в постфиксную форму (алгоритм Дейкстры),
 * 3. Вычисление выражения с интерактивным вводом значений переменных.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "parser.h"

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

int to_postfix(char** tokens, int size, char** postfix)
{
    s_stack stack = { init_char_arr(size, MAX_TOKEN_LEN), -1, MAX_TOKENS };

    char** queue = init_char_arr(size, MAX_TOKEN_LEN); 
    int queue_top = -1;
    char buffer[MAX_TOKEN_LEN];

    // Проход по всем входным токенам
    for ( int i = 0; i < size; i++ )
    {
        // printf("[debug] token: %s\n", tokens[i]);
        // printf("[debug] stack: ");
        // for ( int si = 0; si <= stack.top; si++ )
        //     printf("%s ", stack.elems[si]);
        // printf("\n");

        // printf("[debug] queue: ");
        // for ( int qi = 0; qi <= queue_top; qi++ )
        //     printf("%s ", queue[qi]);
        // printf("\n\n");

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

int evaluate(char** tokens, int size)
{
    s_stack stack = { init_char_arr(size, MAX_TOKEN_LEN), -1, MAX_TOKENS };
    char buffer[MAX_TOKEN_LEN];

    for ( int i = 0; i < size; i++ )
    {
        if ( !strcmp(tokens[i], "") )
            break;

        // printf("[debug] token: \"%s\"\n", tokens[i]);
        // printf("[debug] stack: ");
        // for ( int si = 0; si <= stack.top; si++ )
        //     printf("%s ", stack.elems[si]);
        // printf("\n");

        // Если токен - переменная, добавить в очередь
        if ( !is_operator(tokens[i]) )
        {
            int value = get_value(tokens[i]);
            snprintf(buffer, MAX_TOKEN_LEN, "%d", value);
            push(&stack, buffer);
            continue;
        }

        // Если токен - оператор
        if ( is_operator(tokens[i]) ) 
        {
            int result = 0;

            // Отдельно для унарной операции НЕ
            // из стека извлекается один элемент,
            // а его отрицание кладется обратно
            if ( !strcmp(tokens[i], "NOT") )
            {
                pop(&stack, buffer);
                result = 1 - atoi(buffer);

                snprintf(buffer, MAX_TOKEN_LEN, "%d", result);
                push(&stack, buffer);
                continue;
            }

            // Выбор 2 элементов из стека для
            // бинарных операций
            pop(&stack, buffer);
            int a = atoi(buffer);

            pop(&stack, buffer);
            int b = atoi(buffer);

            // Получение индекса операции в массиве операций
            // для использования его с enum
            int oper_index = get_oper_index(tokens[i]);

            // Вычисление значения на основе индекса оператора
            switch ( oper_index )
            {
                case AND: result = a && b; break;
                case NAND: result = 1 - (a && b); break;
                case OR: result = a || b; break;
                case XOR: result = a ^ b; break;
                case NOR: result = 1 - (a || b); break;
                case IMPL: result = (1 - a) || b; break;
                case EQ: result = a == b; break;
                case NEQ: result = a != b; break;
            }

            // Запись обратно в стек
            snprintf(buffer, MAX_TOKEN_LEN, "%d", result);
            push(&stack, buffer);
        }
    }
    
    // Последний оставшийся в стеке элемент и есть результат
    peek(stack, buffer);
    return atoi(buffer);
}
