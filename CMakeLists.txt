cmake_minimum_required(VERSION 3.16)
project(VH-DSSE)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(OpenSSL REQUIRED)





# load header
INCLUDE_DIRECTORIES(. dynamic static)

# set executable outputs

ADD_EXECUTABLE(StaticTest static/main.cpp static/ClientHandler.cpp static/ServerHandler.cpp static/cuckoo.cpp static/GGMTree.cpp static/Utils.cpp)
ADD_EXECUTABLE(DynamicTest dynamic/Source.cpp dynamic/Client.cpp dynamic/ClientHandler.cpp dynamic/Server.cpp dynamic/cuckoo.cpp dynamic/GGMTree.cpp dynamic/Utils.cpp)

# link
TARGET_LINK_LIBRARIES(StaticTest OpenSSL::Crypto)
TARGET_LINK_LIBRARIES(DynamicTest OpenSSL::Crypto)
