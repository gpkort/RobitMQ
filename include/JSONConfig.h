#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "ConnectionInfo.h"
#include <vector>


class JSONConfig
{
    public:
        JSONConfig(std::string filepath);
        ~JSONConfig(){};
        bool init();

        const ConnectionInfo& ConectionInfo() { return mConnectInfo; }
        
        const std::string HardwareName() { return mHardwareName; }

        const std::vector<std::string>& TopicVector() { return mTopics; }

    private:
        std::string mFilePath;
        std::string mHardwareName;
        ConnectionInfo mConnectInfo;
        std::vector<std::string> mTopics;
        
};

// json J(json_string);
// J["my_list"].get<std::vector<int>>()
