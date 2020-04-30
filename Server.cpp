#include "Server.h"
#include "Config.h"

using namespace std;

void Server::init()
{
    cout << "Initialisation du serveur" << endl;

    ConfigJSON *configJSON = new ConfigJSON();
    int ducksNumber = configJSON->getDucksNumber();

    // initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_socket[i] = 0;
    }

    // create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set master socket to allow multiple connections
    // this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    cout << "Listener on port " << PORT << endl;

    // try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE)
    {
        // clear the socket set
        FD_ZERO(&readfds);

        // add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // add child sockets to set
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            // socket descriptor
            sd = client_socket[i];

            // if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            // highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        // wait for an activity on one of the sockets , timeout is NULL
        // so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            cout << "select error" << endl;
        }

        // If something happened on the master socket ,
        // then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // inform user of socket number - used in send and receive commands
            cout << "New connection , socket fd is " << new_socket << "ip is : " << inet_ntoa(address.sin_addr) << ", port : " << ntohs(address.sin_port) << endl;

            // add new socket to array of sockets
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                // if position is empty
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    client_pool.push_back(new Client(new_socket));

                    cout << "Adding to list of sockets as " << i << endl;

                    break;
                }
            }
        }

        // else its some IO operation on some other socket
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                // Check if it was for closing
                // read also the incoming message
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0)
                {
                    // Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    cout << "Host disconnected , ip " << inet_ntoa(address.sin_addr) << ", port " << ntohs(address.sin_port) << endl;

                    // Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                // Echo back the message that came in
                else
                {
                    // Get message
                    string message(buffer);

                    // Parse and get message type
                    vector<string> elts = Socket::parseMessage(message);
                    enum messageType type = Socket::getMessageType(message);

                    /* Asking configuration */
                    if (type == ASKING_CONFIGURATION)
                    {
                        // Get config data
                        vector<char> config = Server::getConfiguration();

                        // Construct configuration message
                        ConfigurationMessage *configurationMessage = new ConfigurationMessage();
                        configurationMessage->setMessage(config.data());
                        string message = configurationMessage->constructMessage();
                        cout << "Sending configuration" << endl;
                        Socket::sendMessage(sd, message);
                    }
                    else
                    {
                        thread thread(Server::processing, type, message, client_pool, sd);
                        thread.detach();
                    }

                    // set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                }
            }
        }
    }
}

void Server::processing(int type, string message, std::vector<Client *> client_pool, int sd)
{
    /* Duck found */
    if (type == DUCK_FOUND)
    {

        int idPersonWhoFoundDuck = 0;
        int duckNumberPersonWhoFoundDuck = 0;

        ConfigJSON *config = new ConfigJSON();

        for (Client *client : client_pool)
        {
            if (client->getId() == sd)
            {
                client->addDuck();
                idPersonWhoFoundDuck = client->getId();
                duckNumberPersonWhoFoundDuck = client->getDuckNumber();
            }
        }

        string messageToBeSent;
        int idWinner = 0;
        for (Client *client : client_pool)
        {
            if (client->getId() != sd)
            {
                string message = "6@Le client " + to_string(idPersonWhoFoundDuck) + " a trouvé " + to_string(duckNumberPersonWhoFoundDuck) + " canard(s)";
                Socket::sendMessage(client->getId(), message);
            }

            if (client->getDuckNumber() == config->getDucksNumber())
            {
                AllDucksFoundMessage *message = new AllDucksFoundMessage();
                messageToBeSent = message->constructMessage();
                idWinner = client->getId();
            }
        }

        if (idWinner != 0)
        {
            for (Client *client : client_pool)
            {
                string message = messageToBeSent + " par le client " + to_string(idWinner);
                Socket::sendMessage(client->getId(), message);
            }
        }
    }
    else
    {
        Socket::action(message);
    }
}

vector<char> Server::getConfiguration()
{
    // Read the file
    ifstream file(SERVER_CONFIG_FILENAME, ios::binary | ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    vector<char> buffer(size);
    file.read(buffer.data(), size);

    return buffer;
}