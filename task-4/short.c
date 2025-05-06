/**
 * @file short.c
 * @brief Пример обработки коротких опций командной строки в C.
 *
 * Программа демонстрирует использование функции `getopt()` для разбора
 * стандартных коротких опций командной строки.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("Correct options: ");

    // === Проход по опциям === //
    int opt;
    while ( (opt = getopt(argc, argv, "mcst")) != -1 )
    {
        switch ( opt )
        {
            case 'm': printf("m "); break;
            case 'c': printf("c "); break;
            case 's': printf("s "); break;
            case 't': printf("t "); break;
        }
    }

    // === Вывод аргументов не-опций === //
    printf("\nNon-option arguments: ");
    while ( optind < argc )
        printf("%s ", argv[optind++]);

    return 0;
}
