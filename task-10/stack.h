#pragma once

#include <stdio.h>
#include <string.h>

typedef struct
{
    char** elems;
    int top;
    int max_num;
} s_stack;

int is_empty(s_stack stack);

int is_full(s_stack stack);

int push(s_stack* stack, char* value);

int pop(s_stack* stack, char* result);

int peek(s_stack stack, char* result);
