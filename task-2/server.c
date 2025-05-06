/**
 * @file server.c
 * @brief Пример сервера, использующего UNIX-сокеты для межпроцессного взаимодействия (IPC).
 *
 * Сервер создаёт UNIX-сокет, ожидает подключения клиента и переходит в цикл обработки данных,
 * используя функции из заголовочного файла "rw_loop.h".
 *
 * @author Ракитин Илья Алексеевич
 */

#include "rw_loop.h"

int main()
{
    printf(" [i] Server started\n");

    // Создание сокета типа UNIX для IPC
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if ( sockfd == -1 )
    {
        perror(" [E] Error in socket creation!\n");
        exit(EXIT_FAILURE);
    }

    // Установка пути файла, который будет использоваться сокетом
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    // Если файл уже есть, удалить его
    unlink(SOCKET_PATH);

    // Привязка сокета к файлу
    if ( bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1 )
    {
        perror(" [E] Error in bind()\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Ожидание подключения
    if ( listen(sockfd, 5) == -1 )
    {
        perror(" [E] Error in listen()\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    // Получение информации о подключении клиента
    struct sockaddr_un client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if ( client_fd == -1 )
    {
        perror(" [E] Error in accept()\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Вход в цикл чтения-записи
    read_loop(client_fd, "client");

    // Закрытие сокета и удаление файла
    close(sockfd);
    unlink(SOCKET_PATH);

    return 0;
}
