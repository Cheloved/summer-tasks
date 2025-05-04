#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// extern const char* sys_errlist[];

int main()
{
    // Попытка открыть несуществующий файл
    FILE* file = fopen("not_exist.txt", "r");

    // Вывод ошибки через perror()
    if ( !file )
        perror("Ошибка из perror()");

    // Вывод ошибки через strerror()
    if ( !file )
        fprintf(stderr, "Ошибка из strerror(): %s\n", strerror(errno));

    // Вывод только errno
    if ( !file )
        fprintf(stderr, "Ошибка. errno: %d\n", errno);

    // Вывод ошибки через sys_errlist[errno]
    // if ( !file )
    //     fprintf(stderr, "Ошибка из sys_errlist[errno]: %s\n", sys_errlist[errno]);
        
    return 0;
}
