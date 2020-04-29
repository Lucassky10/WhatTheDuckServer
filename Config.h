#ifndef CONFIG_H
#define CONFIG_H

// Définition de la classe Config

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#define SERVER_CONFIG_FILENAME "config.json"

class Config
{
private:
    // Ducks number
    int ducksNumber;
public:

    virtual ~Config() {}
    void setDucksNumber(int);
    int getDucksNumber();
};

class ConfigJSON : public Config
{
public:
    // Config JSON constructor
    ConfigJSON();
};

#endif
