#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <functional>
#include <unordered_map>
#include "GGMTree.h"
#include "cuckoo.h"
# include "ClientHandler.h"
#include "Server.h"
using namespace cuckoo;
using namespace std;


class Client {
private:
    uint32_t N;
    float alpha;
    float beta;

    uint8_t* Kstash = (unsigned char*)"0123456789123456";
    uint8_t* Kbuf = (unsigned char*)"7891234560123456";
    uint8_t* Kske = (unsigned char*)"7891234560123456";
    uint8_t* iv = (unsigned char*)"0123456789123456";
    uint8_t* seed = (unsigned char*)"0123456789123456";
    vector<string> prf_seeds;


    GGMTree* tree;
    KukuTable* table;
    std::vector<string> ESTASH;
    std::vector<string> EBUF;
    std::unordered_map<int, vector<string>> EDBs;
    vector<bool> exist;
    

    ClientHandler* clienthandler;
    Server* server;

    unsigned long get_index(const string& keyword, unsigned short ind);

public:
    Client(int size, float alpha, int mrl);
    ~Client();
    int stash_len;
    void setup(vector<kv> data);
    void update(const string& keyword, int ind, string& text);
    void upload();
    vector<string> search(const string& keyword, int length);
};


#endif //CLIENT_H
