#include "matrix.h"

int global_i = 0;
int global_j = 0;

int** init_mat_square(int size)
{
    int** result = calloc(size, sizeof(int*));
    if ( !result )
    {
        fprintf(stderr, " [E] Ошибка при выделении памяти под матрицу\n");
        return NULL;
    }

    for ( int i = 0; i < size; i++ )
    {
        result[i] = calloc(size, sizeof(int));
        if ( !result[i] )
        {
            fprintf(stderr, " [E] Ошибка при выделении памяти под матрицу\n");
            return NULL;
        }
    }

    return result;
}

int matrix_multiply_square(int size, int** a, int** b, int** result)
{

    return 0;
}

void print_mat(int** mat, int size)
{
    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}
