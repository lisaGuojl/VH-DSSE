
#include <iostream>
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
			sample.op = ADD;
			string id = std::to_string(j);
			sample.text = keywords[i] + id + "ADD";
			data.emplace_back(sample);
		}
	}

	return data;
}


int main() {
	int db_size = 200;
	float alpha = 0.1;
	int a = ceil(db_size * 2 * (1 + alpha));
	//cout << "hash table size:" << a << endl;
	Client client(db_size, alpha, (int)(db_size/2));
	vector<kv> data = generate_samples(db_size);
	client.setup(data);
	cout << "setup completed" << endl;
	vector<string> res = client.search("test");
	cout << "raw search result:" << res.size() << endl;
	vector<int> inds = client.process("test", res);
	cout << "processed search result:" << inds.size() << endl;
	for (auto ind : inds) {
		cout << ind << endl;
	}
	for(int i = 0; i<8; i++){
		client.update("new", i, ADD);
	}
	for (int i = 0; i < 8; i++) {
		client.update("test", i, DEL);
	}
	res.clear();
	inds.clear();
	res = client.search("test");
	inds = client.process("test", res);
	cout << "processed search result:" << inds.size() << endl;
	sort(inds.begin(), inds.end());
	for (auto ind : inds) {
		cout << ind << endl;
	}
	return 0;

}


