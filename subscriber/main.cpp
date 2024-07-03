#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>
#include "../include/JSONConfig.h"
#include "../include/ConnectionInfo.h"
#include "../include/RabbitChannel.h"


using namespace AmqpClient;

const std::string CONFIG_FILE = "RobitMQ.json";

int main(int argc, char** args)
{
    ConnectionInfo ci;
    JSONConfig jc("RobitMQ.json"); 
    RabbitChannel rabbitChannel;   

    if(jc.init())
    {
        auto ci = jc.ConectionInfo();
        
        rabbitChannel.init(ci, jc.HardwareName());

        std::cout << "hw: " << jc.HardwareName() << ", topic: " << jc.TopicVector().size() << std::endl;
        

        while (true)
        {
            Envelope::ptr_t envelope;            
            bool got_msg = rabbitChannel.consumeMessage(envelope);

            if (got_msg)            {
                std::cout << "Received..." << std::endl;
                // routing_key
                auto a = envelope->Message()->Body();
                auto top = envelope->ConsumerTag();
                std::cout << top << std::endl; 
                std::cout << a << std::endl;  
                break;
            }
            else 
            {
                std::cout << "Nothing..." << std::endl;               
            }      
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