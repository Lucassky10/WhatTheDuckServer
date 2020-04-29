#include "Socket.h"

using namespace std;

// Send socket message
void Socket::sendMessage(int socket, string message) {
    send(socket, message.c_str(), strlen(message.c_str()), FLAG_0);
}

// Receive socket message
string Socket::receiveMessage(int socket, char buffer[BUFFER_SIZE]) {
    int valread;
    string message;
    if ((valread = read(socket, buffer, BUFFER_SIZE)) > 0) {
        cout << "Receiving message, processing..." << endl;    
        message = buffer;
    } else {
        message = "-1";
    }
    return message;
}

// Parse socket message
vector<string> Socket::parseMessage(string message) {
    // Elements
    vector<string> elts;
    size_t position;
    string elt;
    while ((position = message.find(DELIMITER)) != string::npos) {
        elt = message.substr(0, position);
        elts.push_back(elt);
        message.erase(0, position + strlen(DELIMITER));
    }
    elts.push_back(message);

    return elts;
}

// Get socket enum message type
enum messageType Socket::getMessageType(string type) {
    int messageTypeNumber = stoi(type);
    return static_cast<messageType>(messageTypeNumber);
}

// Do action
void Socket::action(string message) {
    // Parse and get message type
    vector<string> elts = Socket::parseMessage(message);
    enum messageType type = getMessageType(elts[0]);

    // Do action according by message type
    switch(type) {
        case ASKING_CONFIGURATION:
            cout << "Action: " << enumMessageTypes[ASKING_CONFIGURATION] << endl;            
            break;
        case CONFIGURATION:
            cout << "Action: " << enumMessageTypes[CONFIGURATION] << endl;  
            Socket::configuration(elts);
            break;
        case COORDINATES:
            cout << "Action: Coordonnées x: " << elts[1] << ", y: " << elts[2] << ", : " << elts[3] << endl;
            break;
        default:
            cout << "Message type unknown!" << endl;
    }
}

void Socket::configuration(vector<string> elts) {
    // Construct configuration message
    ConfigurationMessage *configurationMessage = new ConfigurationMessage();
    configurationMessage->setMessage(elts[1]);
    
    // Write config file
    ofstream configFile;
    configFile.open(CLIENT_CONFIG_FILENAME);
    configFile << configurationMessage->getData() << endl;
    cout << "Récupération du fichier de configuration OK" << endl;
}