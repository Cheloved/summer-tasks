#include "rw_loop.h"

int read_loop(int sockfd, char* connect_name)
{
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
            printf("[%s]: %s\n", connect_name, buffer);
        } else {
            char buffer[MAX_MESSAGE_LEN];
            fgets(buffer, MAX_MESSAGE_LEN, stdin);
            write(sockfd, buffer, strlen(buffer)+1);
        }
    }
}
