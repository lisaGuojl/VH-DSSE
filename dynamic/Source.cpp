
#include <iostream>
#include "Client.h"
#include "Utils.h"

using namespace std;


std::string random_string(std::size_t length)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	static std::default_random_engine rng(std::time(nullptr));
	static std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

	std::string str;
	while (str.size() < length) str += alphabet[distribution(rng)];
	return str;
}

vector<kv> generate_samples(int size, int* p) {
	vector<kv> data(0);
	vector<string> keywords = { "test" };
	vector<int> counts = { 1000 };
	int total = counts[0];

	srand(time(NULL));
	while (total < size) {
		int num = 0;
		num = rand() % (1 << 15) + 1;
		if (total + num > size) {
			num = size - total;
		}
		counts.emplace_back(num);
		string keyword = random_string(5);
		keywords.emplace_back(keyword);
		total += num;
	}
	auto it = max_element(std::begin(counts), std::end(counts));
	*p = *it;

	for (int i = 0;i < keywords.size(); i++) {
		cout << keywords[i] << " : " << counts[i] << endl;
		for (int j = 0; j < counts[i];j++) {
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
	int MAXCOUNT = 0;
	cout << "------------------------" << endl;
	cout << "keywords and counts: " << endl;
	vector<kv> dataset = generate_samples(db_size, &MAXCOUNT);
	cout << "maximum response length: " << MAXCOUNT << endl;
	cout << "------------------------" << endl;
  cout << " MRL for query test : " << endl;
	int inputMRL = 0;
	if ((cin >> inputMRL)) {
		MAXCOUNT = inputMRL;
	}
	Client client(db_size, alpha, MAXCOUNT);
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
  int storage = (client.getStashSize() + client.getBufferSize() + client.getEDBSize()) * sizeof(char) * 17;
  cout << "Storage : " << (storage / 1024.0 / 1024.0) << " MB" << endl;


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
	for (int i = 0; i < 8; i++) {
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


