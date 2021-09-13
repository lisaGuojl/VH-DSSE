#include "ClientHandler.h"
#include <iostream>
using namespace cuckoo;
using namespace std;

ClientHandler::ClientHandler(int size, float alpha, string& seedstr) {
	vector<uint8_t> seed(seedstr.begin(), seedstr.end());
	prf_seed = &seed[0];
	tree = new GGMTree(GGM_SIZE);
    item_type empty_item = make_pair((unsigned long)0,"NULL");
	uint32_t table_size = ceil( size * 2 * (1 + alpha));
	table = new KukuTable(table_size, 0, 1, empty_item, prf_seed);
	stash_len = 0;
}

ClientHandler::~ClientHandler() {
	table->clear_table();
	stash.clear();
	edb.clear();
	delete tree;
	delete table;
}


unsigned long ClientHandler::get_index(const string& keyword, unsigned short ind)
{
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	//strncpy((char*)pair, keyword.c_str(), keyword.length() + 1);
	stringcpy((char*)pair, keyword.length() + 1, keyword.c_str());
	
	// get the predix (the hash value of keyword)
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	uint32_t tag = digest[4] | (digest[1] << 8);

	std::bitset<32> bits;
	bits = ind << 1 | (tag << 16) ;
	//std::cout << "add tag" <<bits << std::endl;
	return bits.to_ulong();
}

void ClientHandler::update(const string& keyword, int ind, string& text) {
	
	unsigned long index = get_index(keyword, ind);
	bool res = table->insert(index, text);
	if (res == false) {
		stash_len += 1;
		//stash.push_back(text);
		//std::bitset<32> bits = index;
		string plain = to_string(index) + "0";
		stash.emplace_back(plain);
	}
}


int ClientHandler::setup(vector<kv> db) {
	for (kv item : db) {
		update(item.keyword, item.ind, item.text);
	}
	upload();
	return stash_len;
}



void ClientHandler::upload() {
	for (uint32_t i = 0; i < table->table_size(); ++i) {
		//std::bitset<32> bits = table->table(i).first;
		//string plain = bits.to_string()+"0";
		//plain.insert(plain.length(),"0");
                //cout << plain <<endl;
		string plain = to_string(table->table(i).first)+"0";
		unsigned char* data = new unsigned char[plain.length()+1];
		stringcpy((char*)data, plain.length() + 1, plain.c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[1000] = {};
		ciphertext_len = aes_encrypt(data, plain.length(), key, iv, ciphertext);

		table->insert_by_loc((location_type)(i), reinterpret_cast<char*>(ciphertext));
		//edb.push_back(reinterpret_cast<char*>(ciphertext));
		edb.push_back(string((char*)ciphertext, ciphertext_len));
	}

	for (int j = 0;j < stash.size(); ++j) {
		unsigned char* data = new unsigned char[stash[j].length() + 1];
		//strncpy((char*)data, j.c_str(), j.length() + 1);
		stringcpy((char*)data, stash[j].length() + 1, stash[j].c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[1000] = {};
		ciphertext_len = aes_encrypt(data, stash[j].length(), key, iv, ciphertext);
		stash[j] = string((char*)ciphertext, ciphertext_len);
	}
}


vector<string> ClientHandler::get_edb() {
	return edb;
}
vector<string> ClientHandler::get_estash() {
	return stash;
}

vector<GGMNode> ClientHandler::getToken(const string& keyword, int l, uint8_t* seed)
{
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	//strncpy((char*)pair, keyword.c_str(), keyword.length() + 1);
	stringcpy((char*)pair, keyword.length() + 1, keyword.c_str());

	// get the predix (the hash value of keyword)
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	uint32_t tag = digest[4] | (digest[1] << 8);


	vector<GGMNode> node_list;
	node_list.reserve(2 * l);
	for (int i = 0; i < 2 * l; ++i) {
		std::bitset<32> bits;
		bits = (short int)i | (tag << 16);
		//std::cout << "search tag" << bits << std::endl;
		node_list.emplace_back(GGMNode(bits.to_ulong(), 0));
	}

	vector<GGMNode> remain_node = tree->min_coverage(node_list);
	// compute the key set and send to the server
	for (auto& i : remain_node) {
		i.index = (i.index) << (i.level);
		memcpy(i.digest, seed, 16);
		GGMTree::derive_key_from_tree(i.digest, i.index, tree->get_level(), i.level);

	}

	return remain_node;
}

int ClientHandler::addEDB(vector<string> plains)
{
	for (auto plain : plains) {
		if (plain.length() == 0) {
			continue;
		}
		string index_str = plain.substr(0, plain.length() - 1);
		//bitset<32> index_bit(index_str);
		//uint32_t index = index_bit.to_ulong();
		unsigned long index = stoul(index_str, nullptr, 0);
		bool res = table->insert(index, plain);
		if (res == false) {
			stash_len += 1;
			stash.emplace_back(plain);
		}
	}
	upload();
	return stash_len;
}
