#include "Client.h"

using namespace std;

Client::Client(int socketDescriptor) {
    setId(socketDescriptor);
}

void Client::addDuck() {
    setDuckNumber(getDuckNumber()+1);
}

int Client::getDuckNumber() {
    return duckNumber;
}

void Client::setDuckNumber(int number) {
    duckNumber = number;
}

int Client::getId() {
    return id;
}

void Client::setId(int sd) {
    id = sd;
}