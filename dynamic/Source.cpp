
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
	cout << "Please input the size of the database N." << endl;
	int db_size = 0;
	cin >> db_size;
	cout << "Please input alpha (0<alpha<1)." << endl;
	float alpha = 0;
	cin >> alpha;

	Client client(db_size, alpha, (int)(db_size/2));
	vector<kv> dataset = generate_samples(db_size);
	chrono::high_resolution_clock::time_point time_start, time_end;
	chrono::microseconds time_diff;

	//Setup
	time_start = chrono::high_resolution_clock::now();
	client.setup(dataset);
	time_end = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::microseconds>(time_end - time_start);
	cout << "Setup Done [" << time_diff.count() << " microseconds]" << endl;
  int stash_size = client.getStashSize();
  cout << "Combined Stash size: " << stash_size << endl;


	//Search
	time_start = chrono::high_resolution_clock::now();
	vector<string> res = client.search("test");
	time_end = chrono::high_resolution_clock::now();
	time_diff = chrono::duration_cast<chrono::microseconds>(time_end - time_start);
	cout << "Search Done [" << time_diff.count() << " microseconds]" << endl;

	//Remove the dummy entities in raw search results.
	vector<int> inds = client.process("test", res);
	cout << "processed search result:" << inds.size() << endl;
	//for (auto ind : inds) {
	//	cout << ind << endl;
	//}

	//Update
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
	//for (auto ind : inds) {
	//	cout << ind << endl;
	//}
	return 0;

}


