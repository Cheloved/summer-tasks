#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "reading.h"
#include "matrix.h"

void handle_sigint_signal(int sig)
{
    printf(" Row in a: %d, col in b: %d\n", global_row, global_col); 

    signal(SIGINT, SIG_DFL);
}

void handle_sigint_sigaction(int sig)
{
    printf(" Row in a: %d, col in b: %d\n", global_row, global_col); 

    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, "Укажите способ изменения реакции(signal/sigaction)\n");
        return -1;
    }

    if ( !strcmp(argv[1], "signal") )
    {
        signal(SIGINT, handle_sigint_signal);
    } else if ( !strcmp(argv[1], "sigaction") )
    {
        struct sigaction sa;
        sa.sa_handler = handle_sigint_sigaction;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
    } else {
        fprintf(stderr, "Недоступный способ!\n");
        fprintf(stderr, "Возможные варианты: signal, sigaction\n");
        return -2;
    }

    int** mat_a = init_mat_square(4);
    int** mat_b = init_mat_square(4);
    int** result = init_mat_square(4);

    read_matrix("a.txt", mat_a, 1000, 1000, 16384);
    read_matrix("b.txt", mat_b, 1000, 1000, 16384);

    print_mat(mat_a, 4);
    print_mat(mat_b, 4);
    matrix_multiply_square(4, mat_a, mat_b, result);

    print_mat(result, 4);

    free_mat_square(mat_a, 4);
    free_mat_square(mat_b, 4);
    free_mat_square(result, 4);

    return 0;
}
