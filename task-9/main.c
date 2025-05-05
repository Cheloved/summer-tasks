#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "sequence.h"

int main(int argc, char** argv)
{
    if ( argc != 3 )
    {
        fprintf(stderr, " [E] Должно быть 2 аргумента: путь к файлу и кол-во элементов\n");
        return -1;
    }

    int size = atoi(argv[2]);
    if ( size <= 0 )
    {
        fprintf(stderr, " [E] Неверный размер\n");
        return -2;
    }

    int* seq = (int*)calloc(size, sizeof(int));
    if ( !read_seq("seq.txt", seq, size) )
    {
        for ( int i = 0; i < size; i++ )
            printf("%d ", seq[i]);
    }
    printf("\n");

    int result_size = 0;
    int* result = (int*)calloc(size, sizeof(int));
    find_max_seq(seq, size, result, &result_size);
    
    printf("Максимальная последовательность: ");
    for ( int i = 0; i < result_size; i++ )
        printf("%d ", result[i]);

    free(seq);
    free(result);

    return 0;
}
