#include <iostream>
#include <stdlib.h>

#include "Server.h"

int main(int argc,char **argv)
{
    // Create server and launch initialisation
    Server *server = new Server();
    server->init();

    return EXIT_SUCCESS;
}
