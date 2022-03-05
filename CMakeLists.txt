cmake_minimum_required(VERSION 3.16)
project(VH-DSSE)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(OpenSSL REQUIRED)





# load header
INCLUDE_DIRECTORIES(. dynamic static examples utils dPRF kuku)

# set executable outputs

ADD_EXECUTABLE(StaticTest static/Source.cpp static/ClientHandler.cpp static/ServerHandler.cpp kuku/cuckoo.cpp dPRF/GGMTree.cpp utils/Utils.cpp)
# ADD_EXECUTABLE(DynamicTest dynamic/Source.cpp dynamic/Client.cpp dynamic/ClientHandler.cpp dynamic/Server.cpp kuku/cuckoo.cpp dPRF/GGMTree.cpp utils/Utils.cpp)
# ADD_EXECUTABLE(PerformanceTest examples/examples.cpp examples/SearchTest.cpp examples/UpdateTest.cpp examples/AccuracyTest.cpp dynamic/Client.cpp dynamic/ClientHandler.cpp dynamic/Server.cpp kuku/cuckoo.cpp dPRF/GGMTree.cpp utils/Utils.cpp)
ADD_EXECUTABLE(SetupTest examples/SetupTest.cpp dynamic/Client.cpp dynamic/ClientHandler.cpp dynamic/Server.cpp kuku/cuckoo.cpp dPRF/GGMTree.cpp utils/Utils.cpp)
ADD_EXECUTABLE(SearchTest examples/SetupTest.cpp dynamic/Client.cpp dynamic/ClientHandler.cpp dynamic/Server.cpp kuku/cuckoo.cpp dPRF/GGMTree.cpp utils/Utils.cpp)

# link
TARGET_LINK_LIBRARIES(StaticTest OpenSSL::Crypto)
# TARGET_LINK_LIBRARIES(DynamicTest OpenSSL::Crypto)
# TARGET_LINK_LIBRARIES(PerformanceTest OpenSSL::Crypto)
TARGET_LINK_LIBRARIES(SetupTest OpenSSL::Crypto)
TARGET_LINK_LIBRARIES(SearchTest OpenSSL::Crypto)