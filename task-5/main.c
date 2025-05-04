#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>

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

    if ( file )
        fclose(file);

    // Вывод ошибки через sys_errlist[errno]
    // if ( !file )
    //     fprintf(stderr, "Ошибка из sys_errlist[errno]: %s\n", sys_errlist[errno]);
    
    // В новых реализациях glibc больше не предоставляется 
    // глобальный доступ к sys_errlist,
    // поэтому можно попробовать получить его, 
    // вручную загрузив из динамической библиотеки.
    // 
    // ! Код ниже может не работать, !
    // ! в зависимости от версии     !
    // ! стандартной библиотеки      !

    // Открытие библиотеки
    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if ( !handle )
    {
        fprintf(stderr, "Не удалось открыть libc\n");
        return -1;
    }

    // Получние sys_errlist
    const char*** sys_errlist_ptr = dlsym(handle, "__sys_errlist");

    if ( !sys_errlist_ptr )
    {
        fprintf(stderr, "Не удалось найти sys_errlist\n");
        dlclose(handle);
        return -1;
    } 

    file = fopen("not_exist.txt", "r");
    if ( !file )
        fprintf(stderr, "Ошибка из sys_errlist[errno]: %s\n", sys_errlist_ptr[0][errno]);

    if ( file )
        fclose(file);
    dlclose(handle); 
    return 0;
}
