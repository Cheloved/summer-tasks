#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "reading.h"
#include "matrix.h"

const int SIZE = 1000;

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
        fprintf(stderr, "или generate для генерации матриц a.txt и b.txt");
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
    } else if ( !strcmp(argv[1], "generate") ) {
        generate_matrix("a.txt", SIZE, -10, 10);
        generate_matrix("b.txt", SIZE, -10, 10);
    } else {
        fprintf(stderr, "Неверный аргумент!\n");
        fprintf(stderr, "Возможные варианты: signal, sigaction, generate\n");
        return -2;
    }

    int** mat_a = init_mat_square(SIZE);
    int** mat_b = init_mat_square(SIZE);
    int** result = init_mat_square(SIZE);

    read_matrix("a.txt", mat_a, SIZE, SIZE, 16384);
    read_matrix("b.txt", mat_b, SIZE, SIZE, 16384);

    // print_mat(mat_a, 4);
    // print_mat(mat_b, 4);
    matrix_multiply_square(SIZE, mat_a, mat_b, result);

    // print_mat(result, 4);

    free_mat_square(mat_a, SIZE);
    free_mat_square(mat_b, SIZE);
    free_mat_square(result, SIZE);

    return 0;
}
