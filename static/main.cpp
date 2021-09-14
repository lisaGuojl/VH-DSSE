//#pragma warning(disable:4996)

#include <iostream>
#include "ClientHandler.h"
#include "Utils.h"


using namespace std;
using namespace cuckoo;


int main() {
	int db_size = 900;
	float alpha = 0.1;
	uint32_t a = ceil(db_size * 2 * (1 + alpha));
	cout << "hash table size:"<< a << endl;
	ClientHandler client(db_size, alpha);

	string keyword[3] = { "test", "secure", "sse" };
	string op = "ADD";
	unsigned short i = 0;
	while (i < 300) {
		string id = std::to_string(i);
		string plain = keyword[0] + id + op;
		client.update(keyword[0], i, plain);
		string plain1 = keyword[1] + id + op;
		client.update(keyword[1], i, plain1);
		string plain2 = keyword[2] + id + op;
		client.update(keyword[2], i, plain2);

		i += 1;
	}
	//cout << i << endl;
	cout << "In table:" << i * 3 - client.stash_len << endl;;
	cout << "In stash:" << client.stash_len << endl;
	
	client.upload();


	vector<string> res3 = client.search(keyword[0], 300);
	cout << "search result:" << res3.size() << endl;
	for (auto i : res3) {
		cout << i << endl;
	}
	
	res3.clear();
	return 0;

}


