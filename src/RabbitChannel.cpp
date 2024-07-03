#include <iostream>
#include "RabbitChannel.h"


RabbitChannel::RabbitChannel():
    mHardwareName(""),
    mQueueName(""),
    mConsumerName("") {}

bool RabbitChannel::init( ConnectionInfo& ci, const std::string& hwName)
{
    mHardwareName = hwName;
    AmqpClient::Channel::OpenOpts opts;
    opts.host = ci.getHost();
    opts.port = ci.getPort();
    opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth(ci.getUser(), ci.getPassword());
    std::cout << "Made opts" << std::endl; 

    mChannel = AmqpClient::Channel::Open(opts);
    std::cout << "Opened channel" << std::endl;

    mChannel->DeclareExchange(ci.getExchange(), 
                              AmqpClient::Channel::EXCHANGE_TYPE_TOPIC, 
                              false, true, false);

    mQueueName = mChannel->DeclareQueue("", false, false, true, true);
    mChannel->BindQueue(mQueueName, ci.getExchange(), "camera");
    mConsumerName = mChannel->BasicConsume(mQueueName, "orange-pi");

    return true;
}

bool RabbitChannel::consumeMessage(AmqpClient::Envelope::ptr_t& envelope, const int& timeout) 
{
    std::cout << "Consume " << mConsumerName << ", queue " << mQueueName << std::endl;
    return mChannel->BasicConsumeMessage( mConsumerName, envelope, timeout);
}

bool RabbitChannel::consumeMessage(AmqpClient::Envelope::ptr_t& envelope) 
{
    return this->consumeMessage( envelope, DEFAULT_TIMEOUT);
}
