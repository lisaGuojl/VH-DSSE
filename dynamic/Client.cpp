#include "Client.h"



Client::Client(int size, float a, int mrl) {
	N = size;
	alpha = a;
	beta = (float)mrl / N;
	server = new Server();
	tree = new GGMTree(GGM_SIZE);
	clienthandler = new ClientHandler(alpha);

	for (int i = 0; i <= floor(log2(N)); i++) {
		exist.push_back(false);
	}

	uint8_t base[16] = {};
	memcpy(base, seed, 16);
	for (int i = 0; i <= floor(log2(N)); i++) {
		uint8_t prf_seed[16] = {};
		md5_digest(base, 16, prf_seed);
		std::string str(prf_seed, prf_seed + 16);
		prf_seeds.push_back(str);
		memcpy(base, (unsigned char*)prf_seed, 16);
	}
	MIN = 0;
	
}

Client::~Client() {
	prf_seeds.clear();
	delete tree;
	delete server;
	delete clienthandler;
}

void Client::setup(vector<kv> data) {
  EDBs.clear();
  ESTASH.clear();
  EBUF.clear();
	int idx = 0;
	int logN = floor(log2(N));
	int min = floor(log2(logN));
	std::bitset<32> bits = N;
	MIN = (int)floor(log2(logN));
	for (int i = logN; i >= min; i--) {	
		if (bits[i] == 1) {
			exist[i] = true;
			vector<kv> db(data.begin() + idx, data.begin() + idx + (int)(1 << i));
			int stash_len = clienthandler->setup((int)1 << i, prf_seeds[i], db);
			EDBs[i] = clienthandler->get_edb();
			if (stash_len>0) {
				vector<string> estash = clienthandler->get_estash();
				for (string stash : estash) {
					ESTASH.emplace_back(stash);
				}
			}	
			idx += (int)(1 << i);
		}
	}
	if (idx < N) {
		for (int i = idx;i < N;i++) {
			kv item = data[i];
			unsigned long index = clienthandler->get_index(item.keyword, item.ind);
			string text = to_string(index) + "0";
			unsigned char* data = new unsigned char[text.length() + 1];
			stringcpy((char*)data, text.length() + 1, text.c_str());
			int ciphertext_len = 0;
			unsigned char ciphertext[100] = {};
			ciphertext_len = aes_encrypt(data, text.length(), Kbuf, iv, ciphertext);
			EBUF.emplace_back(string((char*)ciphertext, ciphertext_len));

		}
	}
	server->storeEDB(EDBs, ESTASH, EBUF, min);
	EBUF.clear();
	ESTASH.clear();
	EDBs.clear();
}

string Client::decrypt(string& cipher, uint8_t* key) {
	//unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
	//stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
	unsigned char encrypted_data[1000] = {};
	for (int i = 0; i < (cipher.length());i++) {
		encrypted_data[i] = cipher[i];
	}
	encrypted_data[cipher.length() + 1] = '\0';
	int decryption_len;
	unsigned char decryption_text[1000];
	decryption_len = aes_decrypt(encrypted_data, cipher.length(), key, iv, decryption_text);
	string result = string((const char*)(decryption_text), decryption_len);

	return result;
}

vector<string> Client::search(const string& keyword) {
	vector<string> results;
	for (int i = 0;i < exist.size();i++) {
		if (exist[i] == true) {
			int li = (int)ceil(beta * (int)(1 << i));
			vector<GGMNode> token = {};
			string seedstr = prf_seeds[i];
			vector<uint8_t> prf_seed(seedstr.begin(), seedstr.end());
			token = clienthandler->getToken(keyword, li, &prf_seed[0]);
			vector<string> Xi = server->searchEDB(i, token);
			for (auto cipher : Xi) {
				string plain = decrypt(cipher, Kske);
				results.emplace_back(plain);
			}
			Xi.clear();
		}
	}

	vector<string> stash = server->searchEstash();
	for (auto cipher : stash) {
		string plain = decrypt(cipher, Kstash);
		results.emplace_back(plain);
	}
	stash.clear();

	vector<string> buf = server->searchBuffer();
	for (auto cipher : buf) {
		string plain = decrypt(cipher, Kbuf);
		results.emplace_back(plain);
	}
	buf.clear();

	return results;
}


void Client::update(const string& keyword, int ind, OP op) {
	unsigned long index = clienthandler->get_index(keyword, ind);
	string plain;
	if (op == ADD) {
		plain = to_string(index) + "0";
	}
	else {
		plain = to_string(index) + "1";
	}
	unsigned char* data = new unsigned char[plain.length() + 1];
	stringcpy((char*)data, plain.length() + 1, plain.c_str());
	int ciphertext_len = 0;
	unsigned char ciphertext[100] = {};
	ciphertext_len = aes_encrypt(data, plain.length(), Kbuf, iv, ciphertext);
	//std::string ct(reinterpret_cast<char*>(ciphertext), ciphertext_len/ sizeof(ciphertext[0]));	
	string ct = string((char*)ciphertext, ciphertext_len);
	bool res = server->update(ct);
	if (res == false) {
		updateDB();
	}
	
}


void Client::updateDB() {
	ESTASH.clear();
	vector<string> buf = server->searchBuffer();
	vector<string> stash = server->searchEstash();
	vector<pair<int, vector<string>>> edbs = server->updateDB();

	vector<string> plains = {};
	for (auto cipher : stash) {
		string plain = decrypt(cipher, Kstash);
		if (plain != "NULL") {
			plains.emplace_back(plain);
		}
	}

	for (auto pair : edbs) {
		for (auto cipher : pair.second) {
			string plain = decrypt(cipher, Kske);
			if (plain != "NULL") {
				plains.emplace_back(plain);
			}
		}
	}


	vector<string>  bufplain = {};
	string del = "1";
	for (auto cipher : buf) {
		//unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		//stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		unsigned char encrypted_data[1000] = {};
		for (int i = 0; i < (cipher.length());i++) {
			encrypted_data[i] = cipher[i];
		}
		encrypted_data[cipher.length() + 1] = '\0';
		int decryption_len = 0;
		unsigned char decryption_text[1000] = {};
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kbuf, iv, decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		if (result[result.length() - 1] == del[0]) {
			string delitem = result.substr(0, result.length() - 1) + "0";
			for (vector<string>::const_iterator iter=plains.begin(); iter !=plains.end(); iter++){
        			if (delitem == *iter){
        				iter = plains.erase(iter);
        				break;
        			}
        	}
			bufplain.emplace_back(result);
		}
		else {
        		bufplain.emplace_back(result);
        	}
	}
	
	MIN = MIN+1;
	exist[MIN] = true;
	plains.insert(plains.end(), bufplain.begin(), bufplain.end());
	int stash_len = clienthandler->addEDB((int)(1 << MIN), prf_seeds[MIN], plains);
	vector<string> EDB = clienthandler->get_edb();
	if (stash_len > 0) {
		vector<string> estash = clienthandler->get_estash();
		for (string stash : estash) {
			ESTASH.emplace_back(stash);
		}
	}
	server->storeEDB(MIN, EDB, ESTASH);
	for (auto pair : edbs) {
		exist[pair.first] = false;
	}
}


vector<int> Client::process(const string& keyword, vector<string> plains) {
	uint8_t* pair = new uint8_t[keyword.length() + 1];
	stringcpy((char*)pair, keyword.length() + 1, keyword.c_str());
	uint8_t digest[32] = {};
	sha256_digest(pair, keyword.length(), digest);
	int tag = digest[4] | (digest[1] << 8);

	vector<int> results;
	vector<int> delitems;
	string add = "0";
	for (auto plain : plains) {
		if (plain == "NULL") {
			continue;
		}
		if (plain.length() == 0) {
			continue;
		}
		string result = plain.substr(0, plain.length() - 1);
		int index = stoul(result, nullptr, 0);
		bitset<32> bits(index);
		bitset<16> tagbits;
		for (int i = 0; i < 16;i++) {
			tagbits[i] = bits[i + 16];
		}
		if ((int)(tagbits.to_ulong()) == tag) {
			bitset<15> indbits;
			for (int i = 0; i < 15;i++) {
				indbits[i] = bits[i + 1];
			}
			if (plain[plain.length() - 1] == add[0]) {
				results.emplace_back((int)(indbits.to_ulong()));
			}
			else {
				delitems.emplace_back((int)(indbits.to_ulong()));
			}
			
		}
		
	}
	sort(results.begin(), results.end());
	results.erase(unique(results.begin(), results.end()), results.end());
	for (auto delitem : delitems) {
		for (vector<int>::const_iterator iter = results.begin(); iter != results.end(); iter++) {
			if (delitem == *iter) {
				iter = results.erase(iter);
				break;
			}
		}
	}

	return results;
}

int Client::getStashSize() {
	int res = server->getStashSize();
	return res;
}

int Client::getBufferSize() {
	int res = server->getBufferSize();
	return res;
}

int Client::getEDBSize() {
	int res = 0;
	for (int i = 0;i < exist.size();i++) {
		if (exist[i] == true) {
			res += server->getEDBSize(i);
		}
  }
	return res;
}