#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "dynamic.h"
#include "parser.h"

int main()
{
    const char* expr = "(A AND B) OR (C AND NOT D)";
    // const char* expr = "A AND B OR C ";
    // const char* expr = "A OR B AND C ";

    char** tokens = init_char_arr(MAX_TOKENS, MAX_TOKEN_LEN);

    int tokens_len = tokenize(expr, tokens);

    printf("Token len: %d. Tokens: ", tokens_len);
    for ( int i = 0; i < tokens_len; i++ )
        printf("\"%s\" ", tokens[i]);
    printf("\n");

    to_postfix(tokens, tokens_len);

    return 0;
}
