#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

// extern const char* sys_errlist[];

int main()
{
    // Попытка открыть несуществующий файл
    int file = open("not_exist.txt", O_RDONLY);

    if ( file == -1 )
    {
        // Вывод ошибки через perror()
        perror("Ошибка из perror()");

        // Вывод ошибки через strerror()
        fprintf(stderr, "Ошибка из strerror(): %s\n", strerror(errno));

        // Вывод только errno
        fprintf(stderr, "Ошибка. errno: %d\n", errno);

    } else {
        fclose(file);
    }

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

    file = open("not_exist.txt", O_RDONLY);
    if ( file == -1 )
        fprintf(stderr, "Ошибка из sys_errlist[errno]: %s\n", sys_errlist_ptr[0][errno]);
    else
        fclose(file);

    dlclose(handle); 
    return 0;
}
