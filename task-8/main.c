#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reading.h"
#include "matrix.h"

int main()
{
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
