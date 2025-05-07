/**
 * @file main.c
 * @brief Пример использования системного вызова stat() для получения информации о файле.
 *
 * Программа принимает в командной строке пути к файлам и выводит подробную информацию о каждом:
 * - тип файла,
 * - права доступа,
 - размер,
 - временные метки (доступ, изменение, изменение статуса),
 - UID/GID владельца и др.
 *
 * @author Ракитин Илья Алексеевич
 */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

// === Содержимое структуры, которую получает stat() ===
// struct stat {
//     dev_t      st_dev;      /* ID of device containing file */
//     ino_t      st_ino;      /* Inode number */
//     mode_t     st_mode;     /* File type and mode */
//     nlink_t    st_nlink;    /* Number of hard links */
//     uid_t      st_uid;      /* User ID of owner */
//     gid_t      st_gid;      /* Group ID of owner */
//     dev_t      st_rdev;     /* Device ID (if special file) */
//     off_t      st_size;     /* Total size, in bytes */
//     blksize_t  st_blksize;  /* Block size for filesystem I/O */
//     blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */
// 
//     /* Since POSIX.1-2008, this structure supports nanosecond
//        precision for the following timestamp fields.
//        For the details before POSIX.1-2008, see VERSIONS. */
// 
//     struct timespec  st_atim;  /* Time of last access */
//     struct timespec  st_mtim;  /* Time of last modification */
//     struct timespec  st_ctim;  /* Time of last status change */
// 
// #define st_atime  st_atim.tv_sec  /* Backward compatibility */
// #define st_mtime  st_mtim.tv_sec
// #define st_ctime  st_ctim.tv_sec
// };

/**
 * @brief Выводит информацию о файле по указанному пути.
 *
 * Функция использует системный вызов stat(), чтобы получить данные о файле и
 * выводит их в читаемом виде: тип файла, размер, временные метки, UID/GID, права и т.д.
 *
 * @param path Путь к файлу или директории.
 * @return Возвращает 0 при успехе, -1 при ошибке.
 */
int print_info(char* path)
{
    printf("\n === %s ===\n", path);

    struct stat file_stat;
    if ( stat(path, &file_stat) < 0 )
    {
        perror("Ошбика вызова stat()");
        return -1;
    }

    printf("%-44s | %s\n", "Свойство", "Значение");

    printf("%-46s | %lu\n",
            "ID устройства, которое содержит файл",
            (unsigned long)file_stat.st_dev);

    printf("%-46s | %lu\n",
            "Номер инода",
            (unsigned long)file_stat.st_ino);

    printf("%-57s | %u (0%o)\n",
            "Тип файла и права доступа",
            file_stat.st_mode, file_stat.st_mode);

    printf("%-44s |", "Тип файла");
    switch ( file_stat.st_mode & S_IFMT )
    {
        case S_IFBLK: printf(" %s\n", "Блочное уст-во"); break;
        case S_IFCHR: printf(" %s\n", "Символьное уст-во"); break;
        case S_IFDIR: printf(" %s\n", "Директория"); break;
        case S_IFIFO: printf(" %s\n", "FIFO/pipe"); break;
        case S_IFLNK: printf(" %s\n", "Символьная ссылка"); break;
        case S_IFREG: printf(" %s\n", "Обычный файл"); break;
        case S_IFSOCK: printf(" %s\n", "Сокет"); break;
        default: printf(" %s\n", "Неизвестный тип");
    }

    printf("%-59s | %lu\n",
            "Количество жестких ссылок",
            (unsigned long)file_stat.st_nlink);

    printf("%-45s | %d\n",
            "UID владельца",
            file_stat.st_uid);

    printf("%-45s | %d\n",
            "GID владельца",
            file_stat.st_gid);

    printf("%-54s | %ld\n",
            "Размер файла (в байтах)",
            (long)file_stat.st_size);

    printf("%-58s | %ld\n",
            "Размер блока ввода-вывода",
            (long)file_stat.st_blksize);

    printf("%-62s | %ld\n",
            "Количество выделенных блоков",
            (long)file_stat.st_blocks);

    printf("%-58s | %s",
            "Время последнего доступа",
            ctime(&file_stat.st_atim.tv_sec));

    printf("%-60s | %s",
            "Время последнего изменения",
            ctime(&file_stat.st_mtim.tv_sec));

    printf("%-67s | %s",
            "Время последнего изменения статуса",
            ctime(&file_stat.st_mtim.tv_sec));

    return 0;
}

/**
 * @brief Точка входа программы.
 *
 * Принимает один или несколько путей к файлам в аргументах командной строки.
 * Для каждого файла вызывается функция print_info().
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает 0 при успешном завершении, -1 если не передано ни одного аргумента.
 */
int main(int argc, char** argv)
{
    if ( argc < 2 )
    {
        fprintf(stderr, "Укажите хотя бы один файл для получения информации\n");
        return 1;
    }

    for ( int i = 1; i < argc; i++ )
        print_info(argv[i]);

    return 0;
}
