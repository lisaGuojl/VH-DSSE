//#pragma warning(disable:4996)

#include <iostream>
//#include "ClientHandler.h"
#include "Client.h"
#include "Utils.h"

using namespace std;
using namespace cuckoo;

vector<kv> generate_samples(int size) {
	vector<kv> data(0);
	string keywords[3] = { "test", "dynamic", "sse" };
	int count[3] = { (int)(size / 2), (int)(size / 5), size - (int)(size / 2) - (int)(size / 5) };
	for (int i=0;i < 3;i++) {
		for (int j = 0; j < count[i];j++) {
			kv sample;
			sample.keyword = keywords[i];
			sample.ind = j;
			string id = std::to_string(j);
			sample.text = keywords[i] + id + "ADD";
			data.emplace_back(sample);
		}
	}

	return data;
}


int main() {
	//cout << sizeof(unsigned long) << endl;
	int db_size = 10000;
	float alpha = 0.1;
	uint32_t a = ceil(db_size * 2 * (1 + alpha));
	//cout << "hash table size:" << a << endl;

	//uint8_t* s = (unsigned char*)"0123456789123456";
	//for (int i = 0; i < 16; i++) {
	//	cout << (unsigned char)(*(s+i));
	//}
	//cout << endl;
	//vector<string> list;
	//std::string str(s, s + 16);
	//cout << str << endl;
	//list.emplace_back(str);

	//uint8_t b[16] = {};
	//md5_digest(s, 16, b);
	//s = b;


	//string getstr = list[0];
	//std::vector<uint8_t> myVector(getstr.begin(), getstr.end());
	//uint8_t* c = &myVector[0];
	//for (int i = 0; i < 16; i++) {
	//	cout << (unsigned char)(*c);
	//	c++;
	//}
	Client client(db_size, alpha, (int)(db_size/2));
	vector<kv> data = generate_samples(db_size);
	client.setup(data);
	cout << "setup completed" << endl;

	vector<string> res3 = client.search("test", 300);
        cout << "search result:" << res3.size() << endl;
	for (auto i : res3) {
		cout << i << endl;
	}
	
	res3.clear();
	return 0;

}


