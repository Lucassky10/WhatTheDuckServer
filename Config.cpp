#include "Config.h"

using namespace std;

ConfigJSON::ConfigJSON() {
    ifstream ifs(SERVER_CONFIG_FILENAME);
    Json::Reader reader;
    Json::Value config;
    reader.parse(ifs, config);

    Config::setDucksNumber(config["ducks"].size());
}

// Set ducks number
void Config::setDucksNumber(int numberOfDucks) { ducksNumber = numberOfDucks; }

// Get ducks number
int Config::getDucksNumber() { return ducksNumber; }