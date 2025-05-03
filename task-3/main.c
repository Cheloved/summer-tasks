#include <stdio.h>
#include <string.h>
#include "sorting.h"

int print_help()
{
    return 0;
}

int main(int argc, char** argv)
{
    // if ( argc != 4 )
    // {
    //     print_help();
    //     return -1;
    // }
    
    long size = get_file_size(argv[1]);
    char* buffer = (char*)malloc(size+1);
    read_file(argv[1], size, buffer);
    printf(" [debug] Содержимое файла:\n%s\n", buffer);
    free(buffer);
    return 0;
}
