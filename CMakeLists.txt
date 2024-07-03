project(RobitMQ)
cmake_minimum_required(VERSION 3.2)
set(CLIENT_PATH /usr/local/lib)
set(SUBSCRIBER_EXECUTABLE, "SubRobit")
set(PUBLISHER_EXECUTABLE, "PubRobit")

set(HEAD_DIR ${CMAKE_SOURCE_DIR}/include)
set(HEADER_FILES ${HEAD_DIR}/ConnectionInfo.h 
                  ${HEAD_DIR}/JSONConfig.h 
                  ${HEAD_DIR}/RabbitChannel.h 
                  ${HEAD_DIR}/TopicConstants.h)

add_library(SimpleAmqpClient IMPORTED STATIC)
set_target_properties(SimpleAmqpClient PROPERTIES
    IMPORTED_LOCATION ${CLIENT_PATH}/libSimpleAmqpClient.so)


find_package(Boost COMPONENTS thread REQUIRED)
find_package(nlohmann_json REQUIRED)


include_directories(include )


add_executable(Subscriber src/RabbitChannel.cpp src/JSONConfig.cpp subscriber/main.cpp ${HEADER_FILES})
target_include_directories(Subscriber PRIVATE ${HEAD_DIR})
target_link_libraries(Subscriber SimpleAmqpClient Boost::thread nlohmann_json)

