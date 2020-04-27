#ifndef CONFIG_H
#define CONFIG_H

// Définition de la classe Config

#include <iostream>
#include <fstream>
#include <vector> 
#include <jsoncpp/json/json.h>
#include <gl-matrix.h>
#include <string.h>

#include "Duck.h"

class Config
{
public:

    virtual ~Config() {}
    virtual std::vector<Duck *> loadConfig() = 0;
};

class ConfigJSON : public Config
{
public:

    virtual std::vector<Duck *> loadConfig();
};

#endif
