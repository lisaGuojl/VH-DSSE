#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <functional>
#include <unordered_map>
#include <algorithm>
#include "GGMTree.h"
#include "cuckoo.h"
# include "ClientHandler.h"
#include "Server.h"
using namespace cuckoo;
using namespace std;

struct SetupInput {
    string keyword;
    int count;
    vector<kv> data;
};

class Client {
private:
    int N;
    float alpha;
    float beta;

    uint8_t* Kstash = (unsigned char*)"78912345601234567891234560123456";
    uint8_t* Kbuf = (unsigned char*)"01234567891234560123456789123456";
    uint8_t* Kske = (unsigned char*)"78912345601234567891234560123456";
    uint8_t* iv = (unsigned char*)"01234567891234560123456789123456";
    uint8_t* seed = (unsigned char*)"0123456789123456";
    vector<string> prf_seeds;


    GGMTree* tree;
    std::vector<string> ESTASH;
    std::vector<string> EBUF;
    vector<pair<int, vector<string>>> EDBs;
    vector<bool> exist;
    int MIN;

    ClientHandler* clienthandler;
    Server* server;


    string decrypt(string& cipher, uint8_t* key);
    void processDB(vector<kv>* data);
    vector<kv> constructDB(vector<SetupInput>* input, int size);
    void updateDB();

public:
    Client(int size, float alpha, int mrl);
    ~Client();
    void setup(vector<SetupInput> input);
    vector<string> search(const string& keyword);
    void update(const string& keyword, int ind, OP op);

    vector<int> process(const string& keyword, vector<string> plains);
    int getStashSize();
    int getBufferSize();
    int getEDBSize();
    
    //just for update test
    void clean();
};


#endif //CLIENT_H
