#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <fstream>

#include "Message.h"

#define FLAG_0 0
#define BUFFER_SIZE 1024UL

/* Asking configuration */
#define CONFIG_FILENAME ".config.json"

// Définition de la classe Socket

using namespace std;

class Socket
{
public:
    static void sendMessage(int, string);
    static string receiveMessage(int, char*);
    static vector<string> parseMessage(string);
    static enum messageType getMessageType(string);
    static void action(string message);
    static void configuration(vector<string>);
};

#endif
