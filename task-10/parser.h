#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "dynamic.h"
#include "stack.h"

extern char* OPERATORS[];

int is_operator(char* token);

int to_postfix(char** tokens, int size);
