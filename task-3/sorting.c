#include "sorting.h"

// Получение размера файла
long get_file_size(char* path)
{
    FILE* file = fopen(path, "rb");
    if ( file == NULL )
    {
        printf(" [E] Невозможно открыть файл %s!\n", path);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fclose(file);
    return size;
}

// Считывает содержимое файла
int read_file(char* path, long size, char* result)
{
    FILE* file = fopen(path, "rb");
    if ( file == NULL )
    {
        printf(" [E] Невозможно открыть файл %s!\n", path);
        return -1;
    }

    size_t bytes = fread(result, 1, size, file);
    result[bytes] = 0;

    fclose(file);
    return 0;
}

// Возвращает количество непустых строк
int get_lines_count(char* input, long size)
{
    int count = 0;
    int visible_found = 0;
    for ( long i = 0; i < size+1; i++ )
    {
        if ( (input[i] == '\n' || input[i] == 0) && visible_found )
        {
            count++;
            visible_found = 0;
            continue;
        }

        if ( input[i] != ' ' )
            visible_found = 1;
    }

    return count;
}

// Возвращает массив индексов на начало непустых строк
int get_indexes(char* input, long size, long* result)
{
    int count = 0;
    int start_idx = 0;
    int visible_found = 0;
    for ( long i = 0; i < size+1; i++ )
    {
        if ( input[i] == '\n' || input[i] == 0 )
        {
            if ( visible_found )
                result[count++] = start_idx;

            start_idx = i+1;
            visible_found = 0;
            continue;
        }

        if ( input[i] != ' ' )
            visible_found = 1;
    }

    return 0;
}

// Проверяет доступность способа сортировки
int method_available(char* method)
{
    if ( strcmp(method, "bubble") != 0 )
        return -1;

    if ( strcmp(method, "merge") != 0 )
        return -1;

    if ( strcmp(method, "quick") != 0 )
        return -1;

    return 0;
}

// Сортирует файл input способом method и записывает в output
int sort_file(char* input, char* output, char* method)
{
    if ( !method_available(method) )
    {
        printf(" [E] Метод сортировки %s не поддерживается", method);
        return -1;
    }
    // Получение размера файла и запись в буффер
    long size = get_file_size(input);
    char* buffer = (char*)malloc(size+1);
    read_file(input, size, buffer);
    printf(" [debug] Содержимое файла:\n%s\n", buffer);

    // Получение количества строк
    int lines = get_lines_count(buffer, size);
    printf(" [debug] Кол-во непустых строк: %d\n", lines);

    // Получение индексов начала непустых строк
    long* idxs = (long*)malloc(sizeof(long) * lines);
    get_indexes(buffer, size, idxs);

    // Сортировка
    long* sorted_idxs = (long*)(malloc(sizeof(long) * lines));
    // bubble_sort(buffer, idxs, lines, sorted_idxs);
    // merge_sort(buffer, idxs, lines, sorted_idxs);
    quick_sort(buffer, idxs, lines, sorted_idxs);

    printf("\nInput array: ");
    for ( int i = 0; i < lines; i++ )
        printf("%ld ", idxs[i]);

    printf("\nSorted array: ");
    for ( long i = 0; i < lines; i++ )
        printf("%ld ", sorted_idxs[i]);
    printf("\n");

    char* result_text = (char*)malloc(size);
    lines_concat(buffer, lines, sorted_idxs, result_text);
    printf("Input:\n%s\n", buffer);
    printf("Result:\n%s\n", result_text);

    free(buffer);
    free(idxs);
    free(sorted_idxs);
    free(result_text);

    return 0;
}
