#pragma once

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include "ConnectionInfo.h"
#include <map>
#include <vector>

const int DEFAULT_TIMEOUT = 500;

struct QueueInfo 
{
    std::string QueueName;
    std::function 
}

class RabbitChannel
{
    public:
        RabbitChannel();
        ~RabbitChannel(){};

        bool init( ConnectionInfo& ci, const std::string& hwName); 
        bool consumeMessage(AmqpClient::Envelope::ptr_t& envelope, const int& timeout); 
        bool consumeMessage(AmqpClient::Envelope::ptr_t& envelope);       

        const AmqpClient::Channel::ptr_t Channel();
        const std::string& QueueName() { return mQueueName; }
        const std::string& ConsumerName() { return mQueueName; }


    private:
        // static AmqpClient::Channel::ptr_t mChannel;
        AmqpClient::Channel::ptr_t mChannel;
        std::string mQueueName;
        std::string mConsumerName;
        std::string mHardwareName;
};