#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

class Config
{
    public:
        virtual ~Config() {}
        virtual void loadConfig() = 0;
};

using namespace std;

class ConfigJSON : public Config
{
    public:
        virtual void loadConfig()
        {
            ifstream ifs("config.json");
            Json::Reader reader;
            //TODO: cast to Duck object
            Json::Value config;
            reader.parse(ifs, config);
            // Number of ducks
            cout << "Number of duck: " << config["numberOfDuck"].asString() << endl;
            // Sound played
            cout << "Sound played: " << config["soundPlayed"].asString() << endl;
            /* Ducks */
            // TODO: load ducks
            //string ducks = config["ducks"];
        }
};

/* Test */
int main(int argc,char **argv)
{
    ConfigJSON* configJSON = new ConfigJSON();
    configJSON->loadConfig();
    return EXIT_SUCCESS;
}