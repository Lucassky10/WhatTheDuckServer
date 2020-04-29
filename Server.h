#ifndef SERVER_H
#define SERVER_H

// Définition de la classe Server

#include <iostream>
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <fstream>
#include <vector> 
#include <errno.h>
#include <unistd.h>    //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <array>

#include "Message.h"
#include "Socket.h"

#define TRUE 1
#define FALSE 0
#define PORT 8888
#define MAX_CLIENTS 30
#define BUFFER_SIZE 1024UL
#define FIRST_MESSAGE "ECHO Daemon v1.0 \r\n"
#define SERVER_CONFIG_FILENAME "config.json"

class Server
{
private:
    // Option
    int opt = TRUE;

    // Master socket (starting point)
    int master_socket;

    // Address size
    int addrlen;

    // Socket created
    int new_socket;

    // Socket of clients
    int client_socket[MAX_CLIENTS];

    // select() return file descriptor number
    // select return
    int activity;

    // read return
    int valread;

    // Socket descriptor
    int sd;

    // Max socket descriptor
    int max_sd;

    // Structure describing an Internet socket address
    struct sockaddr_in address;

    //data buffer of BUFFER_SIZE
    char buffer[BUFFER_SIZE];

    // set of socket descriptors
    fd_set readfds;

public:
    void init();
    std::vector<char> getConfiguration();
};

#endif
