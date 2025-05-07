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
            // Если нет, выгрузить из стека всё в очередь
            // до появления левой скобки или оператора 
            // c большим приоритетом
            int priority = get_priority(tokens[i]);
            while ( !is_empty(stack) )
            {
                peek(stack, buffer);

                if ( !strcmp(buffer, "(") )
                    break;

                int top_priority = get_priority(buffer);
                if ( priority < top_priority )
                    break;

                pop(&stack, queue[++queue_top]);
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
        if ( !strcmp(tokens[i], ")") && !is_empty(stack) )
        {
            pop(&stack, buffer);

            while ( strcmp(buffer, "(") && !is_empty(stack) )
            {
                strcpy(queue[++queue_top], buffer);
                memset(buffer, 0, MAX_TOKEN_LEN);
                pop(&stack, buffer);
            }
        }
    }

    // В конце выражения выгружаем весь стек в очередь
    while ( !is_empty(stack) )
        pop(&stack, queue[++queue_top]);

    // Сохранение очереди в результат
    for ( int i = 0; i < queue_top+1; i++ )
        strcpy(postfix[i], queue[i]);

    free_char_arr(stack.elems, size);
    free_char_arr(queue, size);

    return 0;
}

int evaluate(char** tokens, int size)
{
    if ( !tokens || size < 1 )
    {
        fprintf(stderr, " [E] Пустой массив в evaluate()\n");
        return -1;
    }

    s_stack stack = { init_char_arr(size, MAX_TOKEN_LEN), -1, MAX_TOKENS };
    char buffer[MAX_TOKEN_LEN];

    // === Объявление массива переменных === //
    int n_vars = 0;
    s_variable* vars = init_vars_arr(size);
    if ( !vars )
    {
        free_char_arr(stack.elems, size);
        return -1;
    }

    // === Проход по постфиксной записи === //
    for ( int i = 0; i < size; i++ )
    {
        if ( !strcmp(tokens[i], "(") ||
             !strcmp(tokens[i], ")"))
        {
            fprintf(stderr, " [E] Некорректное выражение\n");
            free_char_arr(stack.elems, size); 
            free_vars_arr(vars, size);
            return -1;
        }

        if ( !strcmp(tokens[i], "") )
            break;

        // printf("[debug] token: \"%s\"\n", tokens[i]);
        // printf("[debug] stack: ");
        // for ( int si = 0; si <= stack.top; si++ )
        //     printf("%s ", stack.elems[si]);
        // printf("\n");

        // Если токен - переменная, добавить в стек
        if ( !is_operator(tokens[i]) )
        {
            // Обработка числовых выражений
            if ( !strcmp(tokens[i], "0") )
            {
                push(&stack, "0");
                continue;
            }

            if ( !strcmp(tokens[i], "1") )
            {
                push(&stack, "1");
                continue;
            }

            // Поиск уже занесенных в память переменных
            int var_idx = find_var(vars, n_vars, tokens[i]);
            if ( var_idx >= 0 )
            {
                snprintf(buffer, MAX_TOKEN_LEN, "%d", vars[var_idx].value);
                push(&stack, buffer);
                continue;
            }

            // Если не найдено, создание новой
            int value = get_value(tokens[i]);
            snprintf(buffer, MAX_TOKEN_LEN, "%d", value);
            push(&stack, buffer);

            strcpy(vars[n_vars].name, tokens[i]);
            vars[n_vars].value = value;
            n_vars++;

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
                if ( is_empty(stack) )
                {
                    fprintf(stderr, " [E] Недостаточно переменных для выполнения операции NOT\n");
                    free_char_arr(stack.elems, size); 
                    free_vars_arr(vars, size);
                    return -1;
                }
                pop(&stack, buffer);
                result = 1 - atoi(buffer);

                snprintf(buffer, MAX_TOKEN_LEN, "%d", result);
                push(&stack, buffer);
                continue;
            }

            // Выбор 2 элементов из стека для
            // бинарных операций
            if ( stack.top < 1 )
            {
                fprintf(stderr, " [E] Недостаточно переменных для выполнения бинарной операции\n");
                free_char_arr(stack.elems, size); 
                free_vars_arr(vars, size);
                return -1;
            }
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
                default:
                    fprintf(stderr, " [E] Неизвестный оператор %s\n", tokens[i]);
                    free_char_arr(stack.elems, size); 
                    free_vars_arr(vars, size);
                    return -1;
            }

            // Запись обратно в стек
            snprintf(buffer, MAX_TOKEN_LEN, "%d", result);
            push(&stack, buffer);
        }
    }
    
    if ( is_empty(stack) )
    {
        fprintf(stderr, " [E] Некорректное выражение\n");
        strcpy(buffer, "-1");
    } else
    {
        // Последний оставшийся в стеке элемент и есть результат
        peek(stack, buffer);
    }

    free_char_arr(stack.elems, size); 
    free_vars_arr(vars, size);

    return atoi(buffer);
}
