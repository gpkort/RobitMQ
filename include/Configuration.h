#include <string>

namespace Connection
{

struct ConnectionInfo
{
    std::string mHost;
    int mPort;
    std::string mUser;
    std::string mPassword; 
    std::string mExchange;
    std::string mQueue;  
}

struct Topics
{
    
}
}//Connection