#include <AL/alut.h>

#include "Config.h"

using namespace std;

vector<Duck *> ConfigJSON::loadConfig()
{
    ifstream ifs("config.json");
    Json::Reader reader;
    Json::Value config;
    reader.parse(ifs, config);

    vector<Duck*> ducks;
    int duckNumber = 0;

    for (const auto &jsonDuck : config["ducks"])
    {
        // Get sound played
        string soundPointer = jsonDuck["sound"].asString();
        const char *sound = soundPointer.c_str();

        // Get and create vec3 position
        int xPosition = jsonDuck["position"]["x"].asInt();
        int yPosition = jsonDuck["position"]["y"].asInt();
        int zPosition = jsonDuck["position"]["z"].asInt();
        vec3 position = vec3::fromValues(xPosition, yPosition, zPosition);

        // Get and create vec3 orientation
        int xOrientation = jsonDuck["orientation"]["x"].asInt();
        int yOrientation = jsonDuck["orientation"]["y"].asInt();
        int zOrientation = jsonDuck["orientation"]["z"].asInt();
        vec3 orientation = vec3::fromValues(xOrientation, yOrientation, zOrientation);

        // Show duck
        cout << duckNumber << " " << sound << " " << xPosition << " " << yPosition << " " << zPosition << " " << xOrientation << " " << yOrientation << " " << zOrientation << endl;

        // Create Duck
        Duck *duck = new Duck(duckNumber, sound, position, orientation);
        // Add duck to array
        ducks.push_back(duck);

        // Increment duck number
        duckNumber++;
    }

    return ducks;
}