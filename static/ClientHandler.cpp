#include "ClientHandler.h"
#include <iostream>
using namespace cuckoo;
using namespace std;

ClientHandler::ClientHandler(int size, float alpha) {
	tree = new GGMTree(GGM_SIZE);
        item_type empty_item = make_pair((uint32_t)-1,"NULL");
	uint32_t table_size = ceil( size * 2 * (1 + alpha));
        int stash_size = 0;
	table = new KukuTable(table_size, stash_size, 100, empty_item, prf_seed);
	stash_len = 0;

	server = new ServerHandler(table_size);
}

ClientHandler::~ClientHandler() {
	table->clear_table();
	stash.clear();
	edb.clear();
	delete tree;
	delete table;
	delete server;
}


unsigned long ClientHandler::get_index(const string& keyword, unsigned short ind)
{
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	strncpy((char*)pair, keyword.c_str(), keyword.length() + 1);
	//strcpy_s((char*)pair, keyword.length() + 1, keyword.c_str());
	
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
		stash.push_back(text);
		//cout << stash_len << endl;
	}
}


void ClientHandler::upload() {

	for (uint32_t i = 0; i < table->table_size(); ++i) {
		int plaintext_len = table->table(i).second.length();
		unsigned char* data = new unsigned char[table->table(i).second.length() + 1];
		strncpy((char*)data, table->table(i).second.c_str(), table->table(i).second.length() + 1);
		//strcpy_s((char*)data, table->table(i).second.length() + 1, table->table(i).second.c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[20] = {};
		ciphertext_len = aes_encrypt(data, table->table(i).second.length(), key, iv, ciphertext);

		table->insert_by_loc((location_type)(i), reinterpret_cast<char*>(ciphertext));
		//edb.push_back(reinterpret_cast<char*>(ciphertext));
		edb.push_back(string((char*)ciphertext, ciphertext_len));
	}

	for (int j = 0;j < stash.size(); ++j) {
		unsigned char* data = new unsigned char[stash[j].length() + 1];
		strncpy((char*)data, stash[j].c_str(), stash[j].length() + 1);
		//strcpy_s((char*)data, stash[j].length() + 1, stash[j].c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[20] = {};
		ciphertext_len = aes_encrypt(data, stash[j].length(), key, iv, ciphertext);
		stash[j] = string((char*)ciphertext, ciphertext_len);
	}

	server->addEDB(edb, stash);
}


vector<string> ClientHandler::search(const string& keyword, int l)
{
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	strncpy((char*)pair, keyword.c_str(), keyword.length() + 1);
	//strcpy_s((char*)pair, keyword.length() + 1, keyword.c_str());

	// get the predix (the hash value of keyword)
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	uint32_t tag = digest[4] | (digest[1] << 8);


	vector<GGMNode> node_list;
	node_list.reserve(2*l);
	for (int i = 0; i < 2*l; ++i) {
		std::bitset<32> bits;
		bits = (short int)i | (tag << 16);
		//std::cout << "search tag" << bits << std::endl;
		node_list.emplace_back(GGMNode(bits.to_ulong(), 0));
	}

	vector<GGMNode> remain_node = tree->min_coverage(node_list);
	// compute the key set and send to the server
	for (auto& i : remain_node) {
		i.index = (i.index) << (i.level);
		memcpy(i.digest, prf_seed, 16);
		GGMTree::derive_key_from_tree(i.digest, i.index, tree->get_level(), i.level);		
	}

	vector<string> results;
	vector<string> ciphers = server->search(remain_node);
	for (auto cipher : ciphers) {
		unsigned char encrypted_data[1000] = {};
		for (int i = 0; i < (cipher.length());i++) {
			encrypted_data[i] = cipher[i];
		}
		encrypted_data[cipher.length() + 1] = '\0';
		int decryption_len;
		unsigned char decryption_text[20];
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), key, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	ciphers.clear();
	return results;
}

