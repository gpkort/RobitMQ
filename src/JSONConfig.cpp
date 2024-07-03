#include "../include/JSONConfig.h"

JSONConfig::JSONConfig(std::string filepath): mFilePath(filepath) {}

bool JSONConfig::init()
{
    std::ifstream file(mFilePath);

    if(!file.is_open())
    {
        std::cout << "File " << mFilePath << " can't be opened." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Config File Found!" << std::endl;
    }

    try
    {
        nlohmann::json data = nlohmann::json::parse(file);

        mConnectInfo.init(
            data["rabbitmq"]["host"], 
            data["rabbitmq"]["port"], 
            data["rabbitmq"]["user"], 
            data["rabbitmq"]["password"],
            data["rabbitmq"]["exchange"],
            data["rabbitmq"]["queue"]);

        mHardwareName = data["hardware_name"];
        mTopics = data["topics"].get<std::vector<std::string>>();

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return false;
}