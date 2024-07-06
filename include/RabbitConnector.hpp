#pragma once

#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include <iostream>
#include <thread>

typedef std::function<void(AmqpClient::Envelope::ptr_t& envelope )> RobotCallback;

namespace Rabbit
{

struct ConnectionInfo
{
    std::string host;
    int port;
    std::string user;
    std::string password; 
    std::string exchange;
    int timeout;
};

static std::string mQueueName;
static std::string mConsumerName;
static std::string mExchangeName;
static AmqpClient::Channel::ptr_t mChannel;
ConnectionInfo mConnectionInfo;
static std::map<std::string, RobotCallback> mTopics2Callback;
static int mTimeout;
bool canConsume = true;
bool isConsuming = false;

std::mutex mtx; 


void static checkChannel()
{
    if(!mChannel)
    {
        throw std::runtime_error("Rabbit channel is not open");
    }
};

static void initChannel(ConnectionInfo& ci)
{
    try
    {   
        mExchangeName = ci.exchange;

        AmqpClient::Channel::OpenOpts opts;
        opts.host = ci.host;
        opts.port = ci.port;
        opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth(ci.user, 
                                                            ci.password);

        mChannel = AmqpClient::Channel::Open(opts);
        std::cout << "Opened channel" << std::endl;

        mChannel->DeclareExchange(mExchangeName, 
                                AmqpClient::Channel::EXCHANGE_TYPE_TOPIC, 
                                false, true, false);

        mQueueName = mChannel->DeclareQueue("", false, false, true, true);    
        mConsumerName = mChannel->BasicConsume(mQueueName, "");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
};

bool static SubscribeToTopic(std::string topic, RobotCallback cb)
{
    checkChannel();
    if(mTopics2Callback.count(topic))
    {
        std::cout <<  "Topic does not exist." << std::endl;
        return false;
    }

    mChannel->BindQueue(mQueueName, mExchangeName, topic);
    mTopics2Callback.insert(std::pair<std::string, RobotCallback>(topic, cb));

    return true;   
};

bool static UnsubscribeFromTopic(std::string topic)
{
    checkChannel();
    if(!mTopics2Callback.count(topic))
    {
        std::cout << "Topic does not exists!" << std::endl;
        return false;
    }

    mChannel->UnbindQueue(mQueueName, mExchangeName,  topic);

    return mTopics2Callback.erase(topic);
}; 

void static Consume()
{
    AmqpClient::Envelope::ptr_t envelope;

    while (canConsume)
    {
        auto msg = mChannel->BasicConsumeMessage(mConsumerName, envelope, mTimeout);  

        if(msg)
        {
            std::cout << "Got " << envelope->RoutingKey() << std::endl;
            std::lock_guard<std::mutex> lock(mtx);
            if(mTopics2Callback.count(envelope->RoutingKey()))
            {
                mTopics2Callback[envelope->RoutingKey()](envelope);
            }
        }    
    }

    canConsume = true;
}

void static BeginConsuming()
{
    checkChannel();
    std::cout << "Starting to Consume!" << std::endl;
    if(!isConsuming) 
    {
        isConsuming = true;
        std::thread t1(Consume);
        t1.join();
    }

    isConsuming = false;
    std::cout << "Stoppped Consume!" << std::endl;
};

void static StopConsuming()
{
    std::cout << "Stopping to Consume!" << std::endl;
    canConsume = false;
};



} //Rabbit