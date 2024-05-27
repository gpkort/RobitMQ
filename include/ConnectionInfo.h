#pragma once 

#include <map>
#include <string>

class ConnectionInfo
    {
        public:
            ConnectionInfo() :
                mHost("") ,
                mPort(0),
                mUser(""),
                mPassword(""),
                mExchange(""),
                mQueue("")
                {};
            ~ConnectionInfo()  {};

            void init(std::string host, 
                      int port, 
                      std::string user, 
                      std::string password,
                      std::string exchange,
                      std::string queue) 
            {
                mHost = host,
                mPort = port,
                mUser = user;
                mPassword = password;
                mExchange = exchange;
                mQueue = queue;
            }

            std::string getHost() { return mHost; };
            int getPort() { return mPort; };
            std::string getUser() { return mUser; };
            std::string getPassword() { return mPassword; };
            std::string getExchange() { return mExchange; };
            std::string getQueue() { return mQueue; };

            std::string dump() {
                return "{ \"exchange\":\"" + mExchange + "\", " +
                       "\"queue\":\"" + mQueue + "\", " +
                       "\"host\":\"" + mHost + "\", " +
                       "\"password\":\"" + mPassword + "\", " +
                       "\"port\":\"" + std::to_string(mPort) + "\", " +
                       "\"user\":\"" + mUser + "\" }";
            }

        private:
            std::string mHost;
            int mPort;
            std::string mUser;
            std::string mPassword; 
            std::string mExchange;
            std::string mQueue;    

    }; 