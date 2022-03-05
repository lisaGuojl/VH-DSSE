#include <chrono>
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
//#include <unistd.h>
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

auto Zipf(int num_word, int size, int* p) {
	float sum = 0.0;
	for (int i = 1; i <= num_word; i++) {
		sum += 1.0 / i;
	}

	vector<string> keywords = { "test", "sse", "dynamic", "static" };
	for (int i = 4; i < num_word; i++) {
		string keyword = random_string(5);
		keywords.emplace_back(keyword);
	}

	vector<int> counts = {};
	int count = 0;
	for (int i = 1; i <= num_word; i++) {
		if (i == num_word) {
			int num = size - count;
			count += num;
			counts.emplace_back(num);
		}
		int num = floor(1.0 / i / sum * size);
		counts.emplace_back(num);
		count += num;
	}
	auto it = max_element(std::begin(counts), std::end(counts));
	*p = *it;

	srand(unsigned(time(0)));


	vector<SetupInput> input(0);
	for (int i = 0;i < num_word; i++) {
		cout << keywords[i] << " : " << counts[i] << endl;
		vector<kv> data(0);
		for (int j = 0; j < counts[i]; j++) {
			kv sample;
			sample.keyword = keywords[i];
			sample.ind = j;
			sample.op = ADD;
			//string id = std::to_string(j);
			data.emplace_back(sample);
		}
		input.emplace_back(SetupInput{ keywords[i],counts[i],data });
	}


	return input;
}

vector<kv> generate_samples(int size, int* p) {
	vector<kv> data(0);
	vector<string> keywords = { "test" };
	vector<int> counts = { 500 };
	int total = counts[0];

	srand(time(NULL));
	//srand(unsigned(time(0)));
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
	random_shuffle(data.begin(), data.end());
	return data;
}

int main() {
	cout << "Please input the number of keywords." << endl;
	int num_keywords = 0;
	cin >> num_keywords;
	cout << "Please input the size of the database N." << endl;
	int db_size = 0;
	cin >> db_size;
	cout << "Please input alpha (0<alpha<1)." << endl;
	float alpha = 0;
	cin >> alpha;
	int MAXCOUNT = 0;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "keywords and counts: " << endl;
	vector<SetupInput> input = Zipf(num_keywords, db_size, &MAXCOUNT);
	cout << "maximum response length: " << MAXCOUNT << endl;
	cout << "------------------------" << endl;
	cout << " MRL for query test : " << endl;
	int inputMRL = 0;
	if ((cin >> inputMRL)) {
		MAXCOUNT = inputMRL;
	}
	Client* client = new Client(db_size, alpha, MAXCOUNT);
	chrono::high_resolution_clock::time_point time_start, time_end;
	chrono::microseconds time_diff(0);

	//Setup
	client->setup(input);
	delete client;
	for (int i = 0; i < 10;i++) {
		cout << "Number of try: " << i + 1 << endl;
		client = new Client(db_size, alpha, MAXCOUNT);
		time_start = chrono::high_resolution_clock::now();
		client->setup(input);
		time_end = chrono::high_resolution_clock::now();
		time_diff += chrono::duration_cast<chrono::microseconds>(time_end - time_start);
		delete client;
	}

	cout << "Setup Done [" << time_diff.count() / 10 << " microseconds]" << endl;



	return 0;
}
