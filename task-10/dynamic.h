#pragma once

#include <stdio.h>
#include <stdlib.h>

// Выделяет память под двумерный массив строк
// размером sizex * sizey и возвращает указатель
char** init_char_arr(int sizex, int sizey);

// Освобождает созданный двумерный массив
int free_char_arr(char** ar, int sizex);
