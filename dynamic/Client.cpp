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
	
}

Client::~Client() {
	//table->clear_table();
	EBUF.clear();
	ESTASH.clear();
	EDBs.clear();
	prf_seeds.clear();
	delete tree;
	//delete table;
	delete server;
}

void Client::setup(vector<kv> data) {
	int idx = 0;
	int logN = floor(log2(N));
	int min = floor(log2(logN));
	std::bitset<32> bits = N;

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
			unsigned char* data = new unsigned char[item.text.length() + 1];
			strncpy((char*)data, item.text.c_str(), item.text.length() + 1);
                        //strcpy_s((char*)data, item.text.length() + 1, item.text.c_str());
			int ciphertext_len = 0;
			unsigned char ciphertext[20] = {};
			ciphertext_len = aes_encrypt(data, item.text.length(), Kbuf, iv, ciphertext);
			EBUF.emplace_back(string((char*)ciphertext, ciphertext_len));
		}
	}
	server->addEDB(EDBs, ESTASH, EBUF);
}





vector<string> Client::search(const string& keyword, int l) {
	clienthandler = new ClientHandler(N, alpha, prf_seeds[0]);
  vector<string> results;
	for (int i = 0;i < exist.size();i++) {
		if (exist[i] == true) {
			int li = ceil(beta * (int)(1 << i));
      vector<GGMNode> token = {};
      string seedstr = prf_seeds[i];
			vector<uint8_t> prf_seed(seedstr.begin(), seedstr.end());
			token = clienthandler->getToken(keyword, li, &prf_seed[0]);
			vector<string> Xi = server->searchEDB(i, token);
			for (auto cipher : Xi) {
				unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
				strncpy((char*)encrypted_data, cipher.c_str(), cipher.length() + 1);
				//strcpy_s((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
				int decryption_len;
				unsigned char decryption_text[20];
				decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kske, iv, decryption_text);
				//string result = reinterpret_cast<const char*>(decryption_text);
				string result = string((const char*)(decryption_text), decryption_len);
				results.push_back(result);
			}
			Xi.clear();
		}
	}

	vector<string> stash = server->searchEstash();
	for (auto cipher : stash) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
		strncpy((char*)encrypted_data, cipher.c_str(), cipher.length() + 1);
    //strcpy_s((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len;
		unsigned char decryption_text[20];
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kstash, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	stash.clear();

	vector<string> buf = server->searchBuffer();

	for (auto cipher : buf) {
		unsigned char* encrypted_data = new unsigned char[cipher.length() + 1];
    strncpy((char*)encrypted_data, cipher.c_str(), cipher.length() + 1);
		//strcpy_s((char*)encrypted_data, cipher.length() + 1, cipher.c_str());
		int decryption_len;
		unsigned char decryption_text[20];
		decryption_len = aes_decrypt(encrypted_data, cipher.length(), Kbuf, iv, decryption_text);
		//string result = reinterpret_cast<const char*>(decryption_text);
		string result = string((const char*)(decryption_text), decryption_len);
		results.push_back(result);
	}
	buf.clear();

	return results;
}



