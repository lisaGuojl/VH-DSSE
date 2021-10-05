
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include "examples.h"
using namespace std;

string random_string_u(std::size_t length)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	static std::default_random_engine rng(std::time(nullptr));
	static std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

	std::string str;
	while (str.size() < length) str += alphabet[distribution(rng)];
	return str;
}


vector<kv> generate_samples_u(int size, int* p) {
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
		string keyword = random_string_u(5);
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


int UpdateTest() {
	
	cout << "Please input the size of the database N." << endl;
	int db_size = 0;
	cin >> db_size;
	cout << "Please input alpha (0<alpha<1)." << endl;
	float alpha = 0;
	cin >> alpha;
	int MAXCOUNT = 0;
	cout << "------------------------" << endl;
	cout << "keywords and counts: " << endl;
	vector<kv> dataset = generate_samples_u(db_size, &MAXCOUNT);
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
	client.setup(dataset);
	


	//Update
	cout << "\n" << "Update " << db_size / 4 - 1 << " new kv pairs. Repeat 10 times." << endl; 
  	vector<int> ids;
	vector<int> perres(db_size / 4 - 1);
	vector<int> totaltime;


	for (int count = 0; count < 10; count++) {
		vector<kv> update_data = generate_samples_u(db_size / 4 - 1, &MAXCOUNT);
		cout << count+1 << "-th time" << endl;
		
		for (int i = 0; i < 1000; i++) {
			//cout << i << endl;
			kv data = update_data[i];
			client.update(data.keyword, data.ind, ADD);
    	}
		client.clean();
    	sleep(20);
		for (int i = 0; i < db_size / 4 - 1; i++) {
			kv data = update_data[i];
			time_start = chrono::high_resolution_clock::now();
			client.update(data.keyword, data.ind, ADD);
			time_end = chrono::high_resolution_clock::now();
			perres[i] += chrono::duration_cast<chrono::microseconds>(time_end - time_start).count();
		}
		client.clean();
	}

	int total = 0;
	for (int i = 0; i < db_size / 4 - 1; i++) {
		perres[i] = perres[i] / 10;
		total += perres[i];
		if (i % 16 == 15) {
			//cout << perres[i] << ", ";
			totaltime.emplace_back(total);
			ids.emplace_back(i);
    	}
	}
	
	cout << "Total time: [" << total << " microseconds]" << endl;
	cout << "Average time per update: [" << float(total)/(db_size / 4 - 1) << " microseconds]" << endl;

	//for (auto t : totaltime) {
	//	cout << t << ",";
	//}
 
 
		return 0;
	}
