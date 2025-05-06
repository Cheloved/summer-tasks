/**
 * @file reading.c
 * @brief Реализация функций для чтения и генерации матриц.
 *
 * Файл содержит реализацию двух основных функций:
 * - `read_matrix()` — для чтения матрицы из текстового файла,
 * - `generate_matrix()` — для генерации случайной матрицы и записи её в файл.
 *
 * @author Ракитин Илья Алексеевич
 */

#include "reading.h"

int read_matrix(char* path, int** result, int MAX_ROWS, int MAX_COLS,
                int MAX_LINE_LEN)
{
    FILE* file = fopen(path, "r");
    if ( !file )
    {
        fprintf(stderr, " [E] Невозможно открыть файл %s\n", path);
        return -1;
    }

    char line[MAX_LINE_LEN];
    int row = 0;

    // Считывает по одной строке, пока файл не закончится
    // или пока не дойдет до максимального кол-ва строк
    while ( fgets(line, sizeof(line), file) && row < MAX_ROWS )
    {
        int col = 0;
        char* token = strtok(line, " \n");

        // Копирование чисел, разделенных пробелами
        while ( token && col < MAX_COLS )
        {
            result[row][col++] = atoi(token);
            token = strtok(NULL, " \n");
        }
        row++;
    }

    return 0;
}

int generate_matrix(char* path, int size, int min, int max)
{
    srand((unsigned int)time(NULL));

    FILE* file = fopen(path, "w");
    if ( !file )
    {
        fprintf(stderr, " [E] Не получилось открыть файл для записи\n");
        return -1;
    }

    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
        {
            int value = rand() % (max - min + 1) + min;
            fprintf(file, "%d", value);

            if ( j < size-1 )
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf(" [i] Матрица сгенерирована в %s!\n", path);
    return 0;
}
