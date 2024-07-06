#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>
#include "../include/RabbitConnector.hpp"

#include <iostream>
#include <fstream>


const std::string CONFIG_FILE = "RobitMQ.json";
bool kill = false;

void FromJson(const nlohmann::json& j, Rabbit::ConnectionInfo& ci) 
{
    j.at("host").get_to(ci.host);
    j.at("port").get_to(ci.port);
    j.at("user").get_to(ci.user);
    j.at("password").get_to(ci.password);
    j.at("exchange").get_to(ci.exchange);
    j.at("timeout").get_to(ci.timeout);
}

void camera_move_callback(AmqpClient::Envelope::ptr_t& envelope) 
{
    std::cout << "Received :" << envelope->RoutingKey() << ", " << envelope->Message()->Body() << std::endl;
}

void test_callback(AmqpClient::Envelope::ptr_t& envelope) 
{
    auto mess = envelope->Message()->Body();
    std::cout << "Received :" << envelope->RoutingKey() << ", " << mess << std::endl;
    

    if(mess == "unsubscribe")
    {
        std::cout << "Unsubscribing camera.." << std::endl;
        Rabbit::UnsubscribeFromTopic("camera_move");
    }         
    else if(mess == "subscribe")
    {
        std::cout << "Subscribing camera.." << std::endl;
        Rabbit::SubscribeToTopic("camera_move", camera_move_callback);
    }      
    else if(mess ==  "kill")
    {
        std::cout << "killing" << std::endl;
        kill = true;
        Rabbit::StopConsuming();
    }   
}

int main(int argc, char** args)
{
    
    std::ifstream file(CONFIG_FILE);
    Rabbit::ConnectionInfo ci;

    if(file.is_open())
    {
        nlohmann::json data = nlohmann::json::parse(file);
        FromJson(data, ci);

        std::cout << "port: " << ci.port << ", host: " << ci.host << std::endl;
    }
    else
    {
        std::cout << "File " << CONFIG_FILE << " can't be opened." << std::endl;
        return 1;
    }

    file.close();
    Rabbit::initChannel(ci); 
      

    Rabbit::SubscribeToTopic("test", test_callback);
    Rabbit::SubscribeToTopic("camera_move", camera_move_callback);
    Rabbit::BeginConsuming();
    
    while(!kill) {}
    std::cout << "Goodbye!" << std::endl;
    
    
}


