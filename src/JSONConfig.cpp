#include "../include/JSONConfig.h"

JSONConfig::JSONConfig(std::string filepath): mFilePath(filepath) {}

bool JSONConfig::init(ConnectionInfo& connectionInfo)
{
    std::ifstream file(mFilePath);

    if(!file.is_open())
    {
        std::cout << "File " << mFilePath << " can't be opened." << std::endl;
        return false;
    }
    else
    {
        std::cout << "File Found!" << std::endl;
    }

    try
    {
        nlohmann::json data = nlohmann::json::parse(file);
        std::cout << "File Found!" << data << std::endl;
        std::cout << "host" << data["rabbitmq"]["host"] << std::endl;
        // std::cout << "host" << data["host"] << std::endl;

        connectionInfo.init(
            data["rabbitmq"]["host"], 
            data["rabbitmq"]["port"], 
            data["rabbitmq"]["user"], 
            data["rabbitmq"]["password"],
            data["rabbitmq"]["exchange"],
            data["rabbitmq"]["queue"]);

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return false;
}