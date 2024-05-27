#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "ConnectionInfo.h"



class JSONConfig
{
    public:
        JSONConfig(std::string filepath);
        ~JSONConfig(){};
        bool init(ConnectionInfo& connectionInfo);
    private:
        std::string mFilePath;
        
};