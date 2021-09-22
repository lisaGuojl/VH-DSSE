#include "Server.h"

Server::Server() {

}

Server::~Server() {
    
    EDBs.clear();
    estash.clear();
    buffer.clear();
}

void Server::storeEDB(const vector<pair<int, vector<string>>>& client_edbs, const std::vector<string>& stash, const std::vector<string>& client_buffer, int min_value, int logN) {
    EDBs.clear();
    EDBs.resize(logN+1);
    min = min_value;
    for (auto pair : client_edbs) {
        EDBs[pair.first].assign(pair.second.begin(), pair.second.end());
    }
   

    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }

    buffer.clear();
    buffer = client_buffer;
}


vector<string> Server::searchEDB(int id, const vector<GGMNode>& node_list) {	
    vector<string>* edb;
    edb = &EDBs[id];
    
    vector<string> results;
    
    for (GGMNode n : node_list) {
        std::queue<GGMNode> internal_nodes;
	internal_nodes.push(n);
        int level = n.level;
	while (level > 0){
		GGMNode node = internal_nodes.front();
		//bitset<32> bits(node.index);
		//cout << bits <<endl;
		internal_nodes.pop();
		uint8_t derived_key[16];
		memcpy(derived_key, node.digest, 16);
    		GGMTree::derive_key_from_tree(derived_key, node.index, node.level, node.level-1);
    		internal_nodes.push(GGMNode(node.index, node.level - 1, derived_key));

	    	memcpy(derived_key, node.digest, 16);
    		GGMTree::derive_key_from_tree(derived_key, node.index+ pow(2, node.level - 1), node.level, node.level-1);
    		internal_nodes.push(GGMNode(node.index + pow(2, node.level - 1), node.level - 1, derived_key));
    		level = internal_nodes.front().level;
	}
        while (internal_nodes.empty()) {
	    GGMNode node = internal_nodes.front();
	    internal_nodes.pop();
	    while (true) {
                uint32_t loc32 = node.digest[0] | (node.digest[1] << 8) | (node.digest[2] << 16) | (node.digest[3] << 24);
                int length = ceil(log2(edb->size()));
                uint32_t loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb->size()) {
                    results.emplace_back(edb->at(loc));
                    break;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(node.digest, 16, digest);
                    memcpy(node.digest, digest, 16);
                }
            }
        }

    }


    return results;
}

vector<string> Server::searchEstash() {
    return estash;
}

vector<string> Server::searchBuffer() {
    return buffer;
}


bool Server::update(string ct) {
    buffer.emplace_back(ct);
    if (buffer.size() == (int)(1 << (min +1))) {
        return false;
    }
    return true;
    
}

vector<pair<int, vector<string>>> Server::updateDB() {
    int i = min;
    vector<pair<int, vector<string>>> res={};
    while (true) {
        if (EDBs.empty() != 1 && EDBs[i].size() != 0) {
            res.emplace_back(make_pair(i, EDBs[i]));
            EDBs[i].clear();
            i++;
        }
        else {
            break;
        }
    }
    return res;
}


void Server::storeEDB(int ind, vector<string>& EDB, vector<string>& stash) {
    buffer.clear();
    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }
    if (ind > EDBs.size()) {
	cout << "new!"<<endl;
	vector<string> edb = {};
    	for (auto i : EDB) {
        	edb.emplace_back(i);
    	}
	EDBs.push_back(edb);
    }
    else {
	EDBs[ind].assign(EDB.begin(), EDB.end());
    }
    //min = ind;
}

int Server::getStashSize() {
    return (int)estash.size();
}

int Server::getBufferSize() {
    return (int)buffer.size();
}

int Server::getEDBSize(int i) {
    return (int)EDBs[i].size();
}

