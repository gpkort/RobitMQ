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

    try
    {
        nlohmann::json data = nlohmann::json::parse(file);

        connectionInfo.init(
            data["host"], 
            data["port"], 
            data["user"], 
            data["password"],
            data["exchange"],
            data["queue"]);

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return false;
}