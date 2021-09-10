cmake_minimum_required(VERSION 3.16)
project(VH-DSSE)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(OpenSSL REQUIRED)





# load header
INCLUDE_DIRECTORIES(.)

# set executable outputs

ADD_EXECUTABLE(SSETest main.cpp ClientHandler.cpp ServerHandler.cpp cuckoo.cpp GGMTree.cpp Utils.cpp)

# link

TARGET_LINK_LIBRARIES(SSETest OpenSSL::Crypto)
