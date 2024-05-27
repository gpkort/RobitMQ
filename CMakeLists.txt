project(RobitMQ)
cmake_minimum_required(VERSION 3.2)
set(CLIENT_PATH /usr/local/lib)
set(SUBSCRIBER_EXECUTABLE, "SubRobit")
set(PUBLISHER_EXECUTABLE, "PubRobit")


add_library(SimpleAmqpClient IMPORTED STATIC)
set_target_properties(SimpleAmqpClient PROPERTIES
    IMPORTED_LOCATION ${CLIENT_PATH}/libSimpleAmqpClient.so)


find_package(Boost COMPONENTS thread REQUIRED)
find_package(nlohmann_json REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/include )
# set(SOURCES src/JSONConfig.cpp subscriber/main.cpp)
# file(GLOB SOURCES "src/*.cpp")

set(RobiLib include/JSONConfig.h src/JSONConfig.cpp)


add_executable(Subscriber src/JSONConfig.cpp subscriber/main.cpp)
target_link_libraries(Subscriber SimpleAmqpClient Boost::thread nlohmann_json)

add_executable(Publisher publisher/main.cpp)
target_link_libraries(Publisher SimpleAmqpClient Boost::thread nlohmann_json)
