/**
 * @file long.c
 * @brief Пример обработки длинных опций командной строки в C.
 *
 * Программа демонстрирует использование функции `getopt_long()` для разбора
 * как коротких, так и длинных опций. Также реализована проверка допустимых значений
 * для одной из опций (`--elbrus`).
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/**
 * @brief Проверяет, содержится ли элемент в массиве строк.
 *
 * Используется для проверки допустимых значений опции `--elbrus`.
 *
 * @param array Указатель на массив строк.
 * @param length Длина массива.
 * @param element Строка для поиска.
 * @return Возвращает 1, если элемент найден, иначе — 0.
 */
int contain(char** array, int length, char* element)
{
    if ( !array || !element )
        return -1;

    for ( int i = 0; i < length; i++ )
        if ( !strcmp(array[i], element) )
            return 1;
    
    return 0;
}

/**
 * @brief Обрабатывает ситуацию, когда значение опции некорректно.
 *
 * Выводит сообщение об ошибке и доступные значения, затем завершает программу.
 *
 * @param name Имя опции.
 * @param val Значение опции.
 * @param correct Массив допустимых значений.
 * @param len Длина массива допустимых значений.
 */
void handle_wrong_long(const char* name, char* val, char** correct, int len)
{
    fprintf(stderr, "\n [E] --%s can't be %s!\nAvailable values: ", name, val);
    for ( int i = 0; i < len; i++ )
        printf("%s ", correct[i]);
    exit(1);
}

/**
 * @brief Точка входа программы.
 *
 * Обрабатывает опции командной строки, включая длинную опцию `--elbrus`
 * с ограниченным набором допустимых значений.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Всегда возвращает 0.
 */
int main(int argc, char** argv)
{
    printf("\nCorrect options: ");

    // Структура с допустимыми длинными опциями
    struct option long_options[] = {
        { "elbrus", required_argument, 0, 'e' },
        { 0, 0, 0, 0 }
    };

    // Допустимые варианты опции --elbrus
    char* correct_elbrus[] = { "1c+", "2c+", "2c3", "4c", "8c", "16c" };
    int correct_elbrus_len = 6;

    // === Проход по опциям === //
    int opt;
    int opt_index = 0;
    while ( (opt = getopt_long(argc, argv, "mcste:",
                               long_options, &opt_index)) != -1 )
    {
        switch ( opt )
        {
            case 'm': printf("m "); break;
            case 'c': printf("c "); break;
            case 's': printf("s "); break;
            case 't': printf("t "); break;
            case 'e': 
                if ( contain(correct_elbrus, correct_elbrus_len, optarg) ) 
                    printf("%s=%s ", long_options[opt_index].name, optarg);
                else
                    handle_wrong_long(long_options[opt_index].name,
                                      optarg, correct_elbrus,
                                      correct_elbrus_len);
                break;
        }
    }

    // === Вывод аргументов не-опций === //
    printf("\nNon-option arguments: ");
    while ( optind < argc )
        printf("%s ", argv[optind++]);

    return 0;
}
