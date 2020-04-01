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
            Json::Value config;
            reader.parse(ifs, config);     // Reader can also read strings
            cout << "Number of duck: " << config["numberOfDuck"].asString() << endl;
        }
};

/* Test */
int main(int argc,char **argv)
{
    ConfigJSON* configJSON = new ConfigJSON();
    configJSON->loadConfig();
    return EXIT_SUCCESS;
}