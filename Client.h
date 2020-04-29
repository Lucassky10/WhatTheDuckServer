#ifndef CLIENT_H
#define CLIENT_H

// Définition de la classe Client
using namespace std;


class Client
{
private:

    int id = 0;

    int duckNumber = 0;

public:
    void setId(int);
    int getDuckNumber();
    void setDuckNumber(int);
    int getId();
    void addDuck();
    Client(int);
};

#endif