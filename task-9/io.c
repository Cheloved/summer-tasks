#include "io.h"

int read_seq(char* path, int* result, int size)
{
    FILE* file = fopen(path, "r");
    if ( !file )
    {
        fprintf(stderr, " [E] Невозможно открыть файл %s\n", path);
        return -1;
    }

    char line[MAX_LINE_LEN];
    fgets(line, sizeof(line), file);
    char* token = strtok(line, " \n");

    int i = 0;
    while ( token && i < size )
    {
        result[i++] = atoi(token);
        token = strtok(NULL, " \n");
    }

    return 0;
}
