/**
 * @file dynamic.c
 * @brief Реализация функций для работы с динамическими двумерными массивами строк.
 *
 * Файл содержит реализацию базовых операций над двумерным массивом типа `char**`:
 * - выделение памяти под массив строк,
 * - освобождение памяти.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "dynamic.h"

char** init_char_arr(int sizex, int sizey)
{
    char** result = calloc(sizex, sizeof(char*));
    if ( !result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памятиn");
        return NULL;
    }

    for ( int i = 0; i < sizex; i++ )
    {
        result[i] = calloc(sizey, sizeof(char));
        if ( !result[i] )
        {
            fprintf(stderr, " [E] Ошибка при выделении памяти\n");
            return NULL;
        }
    }

    return result;
}

int free_char_arr(char** ar, int sizex)
{
    for ( int i = 0; i < sizex; i++ )
        if ( ar[i] ) 
            free(ar[i]);

    if ( ar )
        free(ar);

    return 0;
}
