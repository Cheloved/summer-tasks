/**
 * @file main.c
 * @brief Пример работы с обработкой сигналов и умножением матриц.
 *
 * Программа:
 * - позволяет выбрать способ обработки сигнала `SIGINT`: через `signal()` или `sigaction()`,
 * - считывает две матрицы из файлов,
 * - перемножает их,
 * - завершает работу по сигналу `Ctrl+C` после вывода текущих координат вычисления.
 *
 * Также поддерживается режим генерации случайных матриц в файлы `a.txt` и `b.txt`.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "reading.h"
#include "matrix.h"

/**
 * @def SIZE
 * @brief Размер квадратной матрицы (строки и столбцы).
 */
const int SIZE = 1000;

/**
 * @brief Обработчик сигнала SIGINT, использующий стандартную функцию signal().
 *
 * Выводит текущую строку и столбец, на которых остановилось умножение матриц.
 * После первого вызова восстанавливает поведение по умолчанию.
 *
 * @param sig Номер сигнала (ожидается SIGINT).
 */
void handle_sigint_signal(int sig)
{
    printf(" Row in a: %d, col in b: %d\n", global_row, global_col); 

    signal(sig, SIG_DFL);
}

/**
 * @brief Обработчик сигнала SIGINT, использующий функцию sigaction().
 *
 * Выводит текущую строку и столбец, на которых остановилось умножение матриц.
 * После первого вызова восстанавливает поведение по умолчанию.
 *
 * @param sig Номер сигнала (ожидается SIGINT).
 */
void handle_sigint_sigaction(int sig)
{
    printf(" Row in a: %d, col in b: %d\n", global_row, global_col); 

    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(sig, &sa, NULL);
}

/**
 * @brief Точка входа программы.
 *
 * Принимает один аргумент командной строки:
 * - `"signal"` — использовать `signal()` для обработки `SIGINT`,
 * - `"sigaction"` — использовать `sigaction()` для обработки `SIGINT`,
 * - `"generate"` — сгенерировать случайные матрицы в файлы `a.txt` и `b.txt`.
 *
 * Умножает матрицы `a` и `b`, результат записывается в `result`.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает 0 при успешном завершении, отрицательное число в случае ошибки.
 */
int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        fprintf(stderr, "Укажите способ изменения реакции(signal/sigaction)\n");
        fprintf(stderr, "или generate для генерации матриц a.txt и b.txt");
        return 1;
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
        int ret_code1 = generate_matrix("a.txt", SIZE, -10, 10);
        int ret_code2 = generate_matrix("b.txt", SIZE, -10, 10);
        if ( ret_code1 || ret_code2 )
            return 3;

        printf(" [i] Матрицы успешно созданы. Теперь можете запустить main.bin signal/sigaction\n");
        return 0;
    } else {
        fprintf(stderr, "Неверный аргумент!\n");
        fprintf(stderr, "Возможные варианты: signal, sigaction, generate\n");
        return 2;
    }

    int** mat_a = init_mat_square(SIZE);
    int** mat_b = init_mat_square(SIZE);
    int** result = init_mat_square(SIZE);

    read_matrix("a.txt", mat_a, SIZE, SIZE, 16384);
    read_matrix("b.txt", mat_b, SIZE, SIZE, 16384);

    matrix_multiply_square(SIZE, mat_a, mat_b, result);

    free_mat_square(mat_a, SIZE);
    free_mat_square(mat_b, SIZE);
    free_mat_square(result, SIZE);

    return 0;
}
