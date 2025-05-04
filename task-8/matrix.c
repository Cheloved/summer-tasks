#include "matrix.h"

int global_row = 0;
int global_col = 0;

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
    for ( global_row = 0; global_row < size; global_row++ )
    {
        for ( global_col = 0; global_col < size; global_col++ )
        {
            int sum = 0;
            for ( int i = 0; i < size; i++ )    
                sum += a[global_row][i] * b[i][global_col]; 

            result[global_row][global_col] = sum;

            sleep(1);
        }
    }
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
