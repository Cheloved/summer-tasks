/**
 * @file client.c
 * @brief Пример клиента, использующего UNIX-сокеты для межпроцессного взаимодействия (IPC).
 *
 * Сервер создаёт UNIX-сокет, подключается к серверу и переходит в цикл обработки данных,
 * используя функции из заголовочного файла "rw_loop.h".
 *
 * @author Ракитин Илья Алексеевич
 */

#include "rw_loop.h"

int main()
{
    printf(" [i] Client started\n");

    // Создание сокета типа UNIX для IPC
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if ( sockfd == -1 )
    {
        perror(" [E] Error in socket creation!\n");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    struct sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Подключение к серверу
    if ( connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
    {
        perror(" [E] Error in connection!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Вход в цикл чтения-записи
    read_loop(sockfd, "server");

    close(sockfd);

    return 0;
}
