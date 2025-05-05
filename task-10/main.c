#include <stdio.h>
#include <stdlib.h>
#include "token.h"

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

int free_char_arr(char** mat, int sizex)
{
    for ( int i = 0; i < sizex; i++ )
        if ( mat[i] ) 
            free(mat[i]);

    if ( mat )
        free(mat);

    return 0;
}

int main()
{
    const char* expr = "(A AND B) OR (C AND NOT D)";

    char** tokens = init_char_arr(MAX_TOKENS, MAX_TOKEN_LEN);

    int tokens_len = tokenize(expr, tokens);

    printf("Token len: %d\n", tokens_len);
    for ( int i = 0; i < tokens_len; i++ )
        printf("%s\n", tokens[i]);

    return 0;
}
