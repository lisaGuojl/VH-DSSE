#include "Client.h"



Client::Client(int size, float a, int mrl) {
	N = size;
	alpha = a;
	beta = (float)mrl / N;
	server = new Server();
	tree = new GGMTree(GGM_SIZE);

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
	ESTASH.clear();
	EDBs.clear();
	prf_seeds.clear();
	delete tree;
	delete server;
}

void Client::setup(vector<kv> data) {
	int idx = 0;
	int logN = floor(log2(N));
	int min = floor(log2(logN));
	std::bitset<32> bits = N;
	MIN = (int)floor(log2(logN));
	for (int i = logN; i >= min; i--) {	
		if (bits[i] == 1) {
			exist[i] = true;
			clienthandler = new ClientHandler((int)1<<i, alpha, prf_seeds[i]);
			vector<kv> db(data.begin() + idx, data.begin() + idx + (int)(1 << i));
			int stash_len = clienthandler->setup(db);
			EDBs[i] = clienthandler->get_edb();
			if (stash_len>0) {
				vector<string> estash = clienthandler->get_estash();
				for (string stash : estash) {
					ESTASH.emplace_back(stash);
				}
			}	
			delete clienthandler;
			idx += (int)(1 << i);
		}
	}
	if (idx < N) {
		for (int i = idx;i < N;i++) {
			kv item = data[i];
			unsigned long index = clienthandler->get_index(item.keyword, item.ind);
			//std::bitset<32> bits = index;
			string text = to_string(index) + "0";
			unsigned char* data = new unsigned char[text.length() + 1];
			//strncpy((char*)data, table->table(i).second.c_str(), table->table(i).second.length() + 1);
			stringcpy((char*)data, text.length() + 1, text.c_str());
			int ciphertext_len = 0;
			unsigned char ciphertext[100] = {};
			ciphertext_len = aes_encrypt(data, text.length(), Kbuf, iv, ciphertext);
			EBUF.emplace_back(string((char*)ciphertext, ciphertext_len));

		}
	}
	server->storeEDB(EDBs, ESTASH, EBUF, min);
	EBUF.clear();
}



vector<string> Client::search(const string& keyword) {
	clienthandler = new ClientHandler(N, alpha, prf_seeds[0]);
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
				unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
				//strncpy((char*)encrypted_data, table.table(index).c_str(), table.table(index).length() + 1);
				stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
				int decryption_len;
				unsigned char decryption_text[1000];
				decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kske, iv, decryption_text);
				//string result = reinterpret_cast<const char*>(decryption_text);

				string result = string((const char*)(decryption_text), decryption_len);
				results.push_back(result);
			}
			Xi.clear();
		}

	vector<string> stash = server->searchEstash();
	for (auto cipher : stash) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		//strncpy((char*)encrypted_data, table.table(index).c_str(), table.table(index).length() + 1);
		stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len;
		unsigned char decryption_text[100];
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kstash, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	stash.clear();

	vector<string> buf = server->searchBuffer();

	for (auto cipher : buf) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		//strncpy((char*)encrypted_data, table.table(index).c_str(), table.table(index).length() + 1);
		stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len;
		unsigned char decryption_text[100] = {};
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kbuf, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	buf.clear();

	
	}

	return results;
}


void Client::update(const string& keyword, int ind, const string& text) {
	clienthandler = new ClientHandler(MIN, alpha, prf_seeds[0]);
	unsigned long index = clienthandler->get_index(keyword, ind);
	//std::bitset<32> bits = index;
	//string plain = bits.to_string() + "0";
	string plain = to_string(index) + "0";
	unsigned char* data = new unsigned char[plain.length() + 1];
	stringcpy((char*)data, plain.length() + 1, plain.c_str());
	int ciphertext_len = 0;
	unsigned char ciphertext[100] = {};
	ciphertext_len = aes_encrypt(data, plain.length(), Kbuf, iv, ciphertext);
	string ct = string((char*)ciphertext, ciphertext_len);
	bool res = server->update(ct);
	delete clienthandler;
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
	bitset<2> dummy;
	for (auto cipher : stash) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		//strncpy((char*)encrypted_data, table.table(index).c_str(), table.table(index).length() + 1);
		stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len;
		unsigned char decryption_text[100] = {};
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kstash, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		if(result != dummy.to_string()){
			plains.push_back(result);
		}
	}

	for (auto pair : edbs) {
		exist[pair.first] = false;
		for (auto cipher : pair.second) {
			unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
			//strncpy((char*)encrypted_data, table.table(index).c_str(), table.table(index).length() + 1);
			stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
			int decryption_len;
			unsigned char decryption_text[100] = {};
			decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kske, iv, decryption_text);
			//string result = reinterpret_cast<const char*>(decryption_text);
			string result = string((const char*)(decryption_text), decryption_len);
			if(result != dummy.to_string()){
				plains.push_back(result);
			}	
		}

	}

	vector<string>  bufplain = {};
	for (auto cipher : buf) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		stringcpy((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len = 0;
		unsigned char decryption_text[100] = {};
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kbuf, iv, decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		if (result[result.length()]==1){
			string delitem = result.substr(0, result.length() - 1) + "0";
			for (vector<string>::const_iterator iter=plains.begin(); iter !=plains.end(); iter++){
        			if (delitem == *iter){
        				iter = plains.erase(iter);
        				break;
        			}
        		}
		}
		else {
        		bufplain.emplace_back(result);
        	}
	}

		
	MIN = MIN+1;
	exist[MIN] = true;
	plains.insert(plains.end(), bufplain.begin(), bufplain.end());
	clienthandler = new ClientHandler((int)(1<<MIN), alpha, prf_seeds[MIN]);
	int stash_len = clienthandler->addEDB(plains);
	EDBs[MIN] = clienthandler->get_edb();
	if (stash_len > 0) {
		vector<string> estash = clienthandler->get_estash();
		for (string stash : estash) {
			ESTASH.emplace_back(stash);
		}
	}
	delete clienthandler;
	server->storeEDB(MIN, EDBs[MIN], ESTASH);
}
