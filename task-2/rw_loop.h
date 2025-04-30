#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/task2_socket"
#define MAX_MESSAGE_LEN 1024

// Разделяет чтение и запись в сокет на 2 процесса
// и в цикле ожидает входящие данные/ввод
int read_loop(int sockfd, char* connect_name);
