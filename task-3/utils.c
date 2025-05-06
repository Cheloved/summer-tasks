/**
 * @file utils.c
 * @brief Реализация вспомогательных функций для работы со строками в общем буфере.
 *
 * Файл содержит реализацию функций, необходимых для корректной работы алгоритмов сортировки.
 * Эти функции позволяют обрабатывать строки без изменения исходного порядка в памяти.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "utils.h"

int get_line_len(char* input, long idx)
{
    int count = 0;
    while ( input[idx] != '\n' && input[idx] != 0 )
    {
        count++;
        idx++;
    }

    return count;
}

int linecmp(char* input, long a, long b)
{
    // Получение длины строк по индексам их начала
    int len_a = get_line_len(input, a); 
    int len_b = get_line_len(input, b); 

    // === Выделение памяти под промежуточные строки === //
    char* subs_a = (char*)malloc(len_a+1);
    if ( !subs_a )
    {
        fprintf(stderr, " [E] Невозможно выделить память в linecmp()!\n");
        return -1;
    }

    char* subs_b = (char*)malloc(len_b+1);
    if ( !subs_b )
    {
        fprintf(stderr, " [E] Невозможно выделить память в linecmp()!\n");
        free(subs_a);
        return -1;
    }

    // Копирование строк в промежуточные
    strncpy(subs_a, input+a, len_a);
    strncpy(subs_b, input+b, len_b);

    // Убедиться, что установлен нуль-терминатор
    subs_a[len_a] = 0;
    subs_b[len_b] = 0;

    int result = strcmp(subs_a, subs_b);
    free(subs_a);
    free(subs_b);

    return result;
}

int lines_concat(char* input, int lines, long* idxs, char* buffer)
{
    long current_buffer = 0;
    for ( int i = 0; i < lines; i++ )
    {
        long current_input = idxs[i];
        while ( input[current_input] != '\n' && input[current_input] != 0 )
        {
            buffer[current_buffer++] = input[current_input++];
        }
        buffer[current_buffer++] = '\n';
    }

    return 0;
}
