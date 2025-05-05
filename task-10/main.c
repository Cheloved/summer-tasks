#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "dynamic.h"

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
