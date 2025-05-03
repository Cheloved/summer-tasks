#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "utils.h"

int print_help()
{
    printf(" === Сортировка строк текстового файла === \n");
    printf("Использование: main.bin input.txt output.txt method\n");
    printf("Доступные методы: bubble, merge, quick\n");
    return 0;
}

int main(int argc, char** argv)
{
    if ( argc != 4 )
    {
        print_help();
        return -1;
    }

    sort_file(argv[1], argv[2], argv[3]);
    return 0;
}
