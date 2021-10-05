#include <chrono>
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
#include <unistd.h>
using namespace std;


string random_string_s(std::size_t length)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	static std::default_random_engine rng(std::time(nullptr));
	static std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

	std::string str;
	while (str.size() < length) str += alphabet[distribution(rng)];
	return str;
}


vector<kv> generate_samples_s(int size, int* p) {
	vector<kv> data(0);
	vector<string> keywords = { "test" };
	vector<int> counts = { 500 };
	int total = counts[0];

	srand(time(NULL));

	while (total < size) {
		int num = 0;
		num = rand() % (1 << 15) + 1;
		if (total + num > size) {
			num = size - total;
		}
		counts.emplace_back(num);
		string keyword = random_string_s(5);
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
	random_shuffle(data.begin(), data.end());
	return data;
}

int SearchTest() {
	cout << "Please input the size of the database N." << endl;
	int db_size = 0;
	cin >> db_size;
	cout << "Please input alpha (0<alpha<1)." << endl;
	float alpha = 0;

	cin >> alpha;
	int MAXCOUNT = 0;
	cout << "------------------------" << endl;
	cout << "keywords and counts: " << endl;
	vector<kv> dataset = generate_samples_s(db_size, &MAXCOUNT);
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
	
	//Search
	cout << "\n" << "Search Keyword : test" << endl;
	vector<string> res = client.search("test");

	int count = 10;
	chrono::microseconds query_time_sum(0);
	for (int i = 0; i < count; i++) {
		time_start = chrono::high_resolution_clock::now();
		client.search("test");
		time_end = chrono::high_resolution_clock::now();
		cout << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " microseconds]" << endl;
		query_time_sum += chrono::duration_cast<chrono::microseconds>(time_end - time_start);
	}

	cout << "Search Done [Total: " << query_time_sum.count() / count << " us]" << endl;
	cout << "Per result: [" << query_time_sum.count() / count / MAXCOUNT / 1000.0 << " ms]" << endl;

	//Remove the dummy entities in raw search results.
	vector<int> inds = client.process("test", res);
	cout << "processed search result:" << inds.size() << endl;
	for (auto ind : inds) {
	//	cout << ind << endl;
	}



	return 0;
}
