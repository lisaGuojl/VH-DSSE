#include "ClientHandler.h"
#include <iostream>
using namespace cuckoo;
using namespace std;

ClientHandler::ClientHandler(int size, float a) {
	alpha = a;
	table_size = size;
	tree = new GGMTree(GGM_SIZE);
	server = new ServerHandler(table_size);
}

ClientHandler::~ClientHandler() {
	stash.clear();
	edb.clear();
	delete tree;
	delete server;
}


unsigned long ClientHandler::get_index(const string& keyword, unsigned short ind)
{
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	stringcpy((char*)pair, keyword.length() + 1, keyword.c_str());

	// get the predix (the hash value of keyword)
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	uint32_t tag = digest[4] | (digest[1] << 8);

	std::bitset<32> bits;
	bits = ind << 1 | (tag << 16);
	return bits.to_ulong();
}

void ClientHandler::update(const string& keyword, int ind, OP op, string& input_text) {

	unsigned long index = get_index(keyword, ind);
	string text;
	if (op == ADD) {
		text = to_string(index) + "0";
	}
	else {
		text = to_string(index) + "1";
	}
	bool res = table->insert(index, text);
	if (res == false) {
		stash_len += 1;
		stash.emplace_back(text);
	}
}



void ClientHandler::upload() {
	for (uint32_t i = 0; i < table->table_size(); ++i) {
		string plain = table->table(i).second;
		unsigned char* data = new unsigned char[plain.length() + 1];
		stringcpy((char*)data, plain.length() + 1, plain.c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[100] = {};
		ciphertext_len = aes_encrypt(data, plain.length(), key, iv, ciphertext);
		//table->insert_by_loc((location_type)(i), reinterpret_cast<char*>(ciphertext));
		edb.push_back(string((char*)ciphertext, ciphertext_len));
	}

	for (int j = 0;j < stash.size(); ++j) {
		unsigned char* data = new unsigned char[stash[j].length() + 1];
		stringcpy((char*)data, stash[j].length() + 1, stash[j].c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[100] = {};
		ciphertext_len = aes_encrypt(data, stash[j].length(), key, iv, ciphertext);
		stash[j] = string((char*)ciphertext, ciphertext_len);
	}
	server->addEDB(edb, stash);
}

int ClientHandler::setup(vector<kv> db) {
	stash_len = 0;
	edb.clear();
	stash.clear();
	int size = db.size();
	uint32_t table_size = ceil(size * 2 * (1 + alpha));
	item_type empty_item = make_pair((unsigned long)0, "NULL");
	int eviction = 5 * log(size);
	table = new KukuTable(table_size, 0, eviction, empty_item, prf_seed);
	for (kv item : db) {
		update(item.keyword, item.ind, item.op, item.text);
	}
	upload();
	delete table;
	return stash_len;
}

vector<GGMNode> ClientHandler::getToken(const string& keyword, int l) {
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	stringcpy((char*)pair, keyword.length() + 1, keyword.c_str());

	// get the predix (the hash value of keyword)
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	uint32_t tag_keyword = digest[4] | (digest[1] << 8);

	vector<GGMNode> remain_node;

	bitset<16> lbits(2 * l - 1);
	vector<int> zero_list = {};
	vector<int> one_list = {};
	bitset<16> tag_ind;
	bitset<32> tag;
	for (int i = 0; i < 16;i++) {
		if (lbits[i] == 0) {
			zero_list.emplace_back(i);
		}
		else {
			one_list.emplace_back(i);
		}
	}

	int Imax = one_list.back();
	// l = 2 ^ 15.
	if (zero_list.size() == 0) {
		tag = (short int)0 | (tag_keyword << 16);
		remain_node.emplace_back(GGMNode(tag.to_ulong(), Imax + 1));
	}

	int Omin = zero_list[0];
	int Omax = zero_list.back();
	// l = 2 ^ x
	if (Omin == Imax + 1) {
		tag = (short int)0 | (tag_keyword << 16);
		remain_node.emplace_back(GGMNode(tag.to_ulong(), Imax + 1));
	}
	else {
		for (int ind = Imax; ind > Omin; ind--) {
			if (lbits[ind] == 1) {
				tag.reset();
				tag_ind.reset();
				for (int iter = 15; iter > ind; iter--) {
					tag_ind[iter] = lbits[iter];
				}
				tag = (short int)(tag_ind.to_ulong()) | (tag_keyword << 16);
				remain_node.emplace_back(GGMNode(tag.to_ulong(), ind));
			}
		}
		tag.reset();
		tag.reset();
		for (int iter = 15; iter > Omin; iter--) {
			tag_ind[iter] = lbits[iter];
		}
		tag = (short int)(tag_ind.to_ulong()) | (tag_keyword << 16);
		remain_node.emplace_back(GGMNode(tag.to_ulong(), Omin));
	}

	// compute the key set and send to the server
	for (auto& i : remain_node) {
		memcpy(i.digest, prf_seed, 16);
		GGMTree::derive_key_from_tree(i.digest, i.index, tree->get_level(), i.level);
	}

	return remain_node;
}

vector<string> ClientHandler::search(const string& keyword, int l)
{
	vector<GGMNode> remain_node = getToken(keyword, l);
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
		unsigned char decryption_text[1000];
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), key, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	ciphers.clear();
	return results;
}

