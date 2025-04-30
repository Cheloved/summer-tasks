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

    // Родительский процесс ждет сообщения и выводит его,
    // а дочерний ожидает пользовательского ввода
    while( 1 )
    {
        if ( pid == 0 )
        {
            char buffer[MAX_MESSAGE_LEN];
            fgets(buffer, MAX_MESSAGE_LEN, stdin);
            write(sockfd, buffer, strlen(buffer)+1);
        } else {
            char buffer[MAX_MESSAGE_LEN];
            int ret_code = read(sockfd, buffer, sizeof(buffer));
            if ( ret_code == 0 )
            {
                printf(" [E] Connection lost!\n");
                kill(pid, SIGTERM);
                return -1;
            }
            printf("[%s]: %s\n", connect_name, buffer);
        }
    }
}
