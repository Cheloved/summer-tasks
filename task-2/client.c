#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/task2_socket"
#define MAX_MESSAGE_LEN 1024

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

    // Разделение на 2 процесса - чтения и записи
    pid_t pid = fork();

    if ( pid < 0 )
    {
        printf(" [ERROR] on fork\n");
        exit(EXIT_FAILURE);
    }

    // Дочерний процесс ждет сообщения и выводит его,
    // а родительский ожидает пользовательского ввода
    while( 1 )
    {
        if ( pid == 0 )
        {
            char buffer[MAX_MESSAGE_LEN];
            read(sockfd, buffer, sizeof(buffer));
            printf("[server]: %s\n", buffer);
        } else {
            char buffer[MAX_MESSAGE_LEN];
            fgets(buffer, MAX_MESSAGE_LEN, stdin);
            write(sockfd, buffer, strlen(buffer));
        }
    }

    close(sockfd);

    return 0;
}
