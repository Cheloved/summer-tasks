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
    while ( fgets(line, sizeof(line), file) && row < MAX_ROWS )
    {
        int col = 0;
        char* token = strtok(line, " \n");

        while ( token && col < MAX_COLS )
        {
            result[row][col++] = atoi(token);
            token = strtok(NULL, " \n");
        }
        row++;
    }

    return 0;
}
