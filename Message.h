#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#define DELIMITER "@"

// Définition de la classe Message

using namespace std;

/* Enum: Message type */
enum messageType { ASKING_CONFIGURATION, CONFIGURATION, DUCK_FOUND, DUCK_FOUND_CLIENT, ALL_DUCKS_FOUND, COORDINATES };
/* Enum strings */
static const string enumMessageTypes[] = { "Demande de la configuration", "Configuration", "Canard trouvé", "Le client %s a trouvé %i canard(s)", "Tous les canards ont été trouvés", "x: %i, y: %i, z: %i" };

class Message
{
public:
    // Type
    messageType type;
    string message;

    virtual ~Message() {}
    virtual string constructMessage() = 0;
    messageType getType();
    string getTextForEnum(int);
};

// 1. Asking configuration message sent by client
class AskingConfigurationMessage : public Message
{
private:

public:
    AskingConfigurationMessage();
    string constructMessage();
};

// 2. Config initialisation
class ConfigurationMessage : public Message
{
private:

    // Config (ducks)
    string data;

public:
    ConfigurationMessage();
    string constructMessage();
    void setMessage(string);
    string getData();
    void setData(string);
};

// 3. Duck found
class DuckFoundMessage : public Message
{
private:
    // Duck found type
    messageType type = DUCK_FOUND;

    // Duck id
    int duckId;

public:
    // Get duck id
    int getDuckId();
};

// 4. Duck found by a client
class DuckFoundClientMessage : public Message
{
private:
    // Duck found by a client type
    messageType type = DUCK_FOUND_CLIENT;

public:
    
};

// 5. All ducks found
class AllDucksFoundMessage : public Message
{
private:

public:
    AllDucksFoundMessage();
    string constructMessage();    
};

// 6. Coordinates sent by client
class CoordinatesMessage : public Message
{
private:
    // Position (x, y, z)
    int position[3];

public:
    CoordinatesMessage();
    string constructMessage();
    // Set position
    void setPosition(int, int, int);
    // Get position
    int* getPosition();
};

#endif
