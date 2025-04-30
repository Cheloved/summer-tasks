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
            read(client_fd, buffer, sizeof(buffer));
            printf("[client]: %s\n", buffer);
        } else {
            char buffer[MAX_MESSAGE_LEN];
            fgets(buffer, MAX_MESSAGE_LEN, stdin);
            write(client_fd, buffer, strlen(buffer));
        }
    }

    close(sockfd);
    unlink(SOCKET_PATH);

    return 0;
}
