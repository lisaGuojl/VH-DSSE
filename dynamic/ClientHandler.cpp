#include <iostream>
#include "ClientHandler.h"

ClientHandler::ClientHandler(float a) {
	alpha = a;
	tree = new GGMTree(GGM_SIZE);
	stash_len = 0;
}

ClientHandler::~ClientHandler() {
	stash.clear();
	edb.clear();
	delete tree;

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

void ClientHandler::update(const string& keyword, int ind, OP op, string& text) {

	unsigned long index = get_index(keyword, ind);

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
		unsigned char ciphertext[1000] = {};
		ciphertext_len = aes_encrypt(data, plain.length(), Kske, iv, ciphertext);
		//table->insert_by_loc((location_type)(i), reinterpret_cast<char*>(ciphertext));
		edb.push_back(string((char*)ciphertext, ciphertext_len));
	}

	for (int j = 0;j < stash.size(); ++j) {
		unsigned char* data = new unsigned char[stash[j].length() + 1];
		stringcpy((char*)data, stash[j].length() + 1, stash[j].c_str());
		int ciphertext_len = 0;
		unsigned char ciphertext[1000] = {};
		ciphertext_len = aes_encrypt(data, stash[j].length(), Kstash, iv, ciphertext);
		stash[j] = string((char*)ciphertext, ciphertext_len);
	}
}


int ClientHandler::setup(int size, string& seedstr, vector<kv> db) {
	stash_len = 0;
	edb.clear();
	stash.clear();
	vector<uint8_t> seed(seedstr.begin(), seedstr.end());
	prf_seed = &seed[0];
	uint32_t table_size = ceil(size * 2 * (1 + alpha));
	item_type empty_item = make_pair((unsigned long)0, "NULL");
	int eviction = ceil(5 * log(size));
	table = new KukuTable(table_size, 0, eviction, empty_item, prf_seed);
	for (kv item : db) {
		update(item.keyword, item.ind, item.op, item.text);
	}
	upload();
	delete table;
	return stash_len;
}

vector<string> ClientHandler::get_edb() {
	return edb;
}
vector<string> ClientHandler::get_estash() {
	return stash;
}

vector<GGMNode> ClientHandler::getToken_min_coverage(const string& keyword, int l, uint8_t* seed)
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

vector<GGMNode> ClientHandler::getToken(const string& keyword, int l, uint8_t* seed) {
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
		memcpy(i.digest, seed, 16);
		GGMTree::derive_key_from_tree(i.digest, i.index, tree->get_level(), i.level);
	}

	return remain_node;
}

int ClientHandler::addEDB(int size, string& seedstr, vector<string> plains)
{
	stash_len = 0;
	stash.clear();
	edb.clear();
	vector<uint8_t> seed(seedstr.begin(), seedstr.end());
	prf_seed = &seed[0];
	uint32_t table_size = ceil(size * 2 * (1 + alpha));
	item_type empty_item = make_pair((unsigned long)0, "NULL");
	int eviction = 5 * log(size);
	table = new KukuTable(table_size, 0, eviction, empty_item, prf_seed);
	unordered_map<unsigned long, int> map;
	for (auto plain : plains) {
		if (plain.length() == 0) {
			continue;
		}
		string index_str = plain.substr(0, plain.length() - 1);
		unsigned long index = stoul(index_str, nullptr, 0);
		bitset<32> bits(index);
		bitset<16> tagbits;
		bitset<32> addrbits;
		for (int i = 0; i < 16;i++) {
			tagbits[i] = bits[i + 16];
		}
		auto it = map.find(tagbits.to_ulong());
		if (it == map.end()) {
			map[tagbits.to_ulong()] = 0;
			addrbits = (unsigned short)0 << 1 | tagbits.to_ulong() << 16;
		}
		else {
			it->second += 1;
			addrbits = (unsigned short)(it->second) << 1 | tagbits.to_ulong() << 16;
		}
		bool res = table->insert(addrbits.to_ulong(), plain);
		if (res == false) {
			stash_len += 1;
			stash.emplace_back(plain);
		}
	}
	upload();
	delete table;
	return stash_len;
}
