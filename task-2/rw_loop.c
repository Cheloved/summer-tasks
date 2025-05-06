/**
 * @file rw_loop.c
 * @brief Реализация функции read_loop() для работы с циклом чтения/записи через UNIX-сокет.
 *
 * Файл содержит реализацию функции, которая создаёт два процесса: один читает данные из сокета,
 * второй — отправляет введённые пользователем данные в сокет. Обмен происходит до разрыва соединения.
 *
 * @author Ракитин Илья Алексеевич
 */

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
    // и отправляет данные

    if ( pid == 0 )
    {
        // Считывает данные из stdin до EOF
        char buffer[MAX_MESSAGE_LEN];
        while ( fgets(buffer, MAX_MESSAGE_LEN, stdin) )
            write(sockfd, buffer, strlen(buffer)+1);

        close(sockfd);
        exit(EXIT_SUCCESS);
    } else {
        char buffer[MAX_MESSAGE_LEN];
        while (1)
        {
            // Пока соединение установлено, получает данные через сокет
            int ret_code = read(sockfd, buffer, sizeof(buffer));
            if ( ret_code == 0 )
            {
                printf(" [E] Connection lost!\n");
                kill(pid, SIGTERM);
                waitpid(pid, NULL, 0); // Ожидание завершения дочернего процесса
                break;
            }
            printf("[%s]: %s\n", connect_name, buffer);
        }
    }

    return 0;
}
