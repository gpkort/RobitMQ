#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>
#include "../include/JSONConfig.h"
#include "../include/ConnectionInfo.h"


using namespace AmqpClient;

const std::string TOPIC = "snapshot.take";
const std::string CONFIG_FILE = "RobitMQ.json";

int main(int argc, char** args)
{
    ConnectionInfo ci;
    JSONConfig jc("RobitMQ.json");

    if(jc.init(ci))
    {
        std::cout << "Test: " << ci.dump() << std::endl;

        Channel::OpenOpts opts;
        opts.host = ci.getHost();
        opts.port = ci.getPort();
        opts.auth = Channel::OpenOpts::BasicAuth(ci.getUser(), ci.getPassword());
        std::cout << "Made opts" << std::endl; 

        auto subChannelPtr = Channel::Open(opts);
        std::cout << "Opened channel" << std::endl;

        subChannelPtr->DeclareExchange(ci.getExchange(), 
                                      Channel::EXCHANGE_TYPE_TOPIC, 
                                      false, true, false);

        auto queueName = subChannelPtr->DeclareQueue("", false, false, true, true);
        subChannelPtr->BindQueue(queueName, 
                             ci.getExchange(), 
                            TOPIC);
        auto consumerName = subChannelPtr->BasicConsume(queueName, "camera");

        while (1)
        {
            std::string a;
            Envelope::ptr_t envelope;

            bool got_msg = subChannelPtr->BasicConsumeMessage( consumerName, envelope);
            if (!got_msg)
            {
                std::cout << "timeout\n" << std::endl;
                break;
            }

            a = envelope->Message()->Body();
            std::cout << a << std::endl;            
        }
    }
    

    
    
    

    
    
}


/*
subChannelPtr->DeclareExchange("robot", AmqpClient::Channel::EXCHANGE_TYPE_TOPIC, false, true, false);
    auto queueName = subChannelPtr->DeclareQueue("", false, false, true, true);
    subChannelPtr->BindQueue(queueName, "","");

    std::cout << "Queue Name: " << queueName << std::endl;

    

    auto consumeName = subChannelPtr->BasicConsume(queueName, "camera");

    std::cout << "Consume Name: " << consumeName << std::endl;

    // auto got_msg = subChannelPtr->BasicConsumeMessage( mConsumerTag, message, timeout );

    while(1){
        

    m_channel->BasicConsume(m_consumerQueue, m_consumerQueue);
    }

    return 0;
*/