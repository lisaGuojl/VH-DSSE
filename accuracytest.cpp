
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
using namespace std;

vector<pair<string, int>> first4 = {};
vector<kv> ADDdata(0);

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
	vector<int> counts = { 50 };
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
			if (i < 4 && j > ceil(counts[i] * 0.95)) {
				ADDdata.emplace_back(sample);
			}
			else{
				data.emplace_back(sample);
			}			
		}
	}
	random_shuffle (data.begin(), data.end());
	for(auto d:data){
		cout<<d.keyword<<endl;
	}
	return data;
}

int myrandom (int i) { return std::rand()%i;}


vector<kv> Zipf(int num_word, int size, int* p) {
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
  for (int i = 0;i < 4; i++) {
    first4.emplace_back(make_pair(keywords[i], counts[i]));
  }
 
	srand(unsigned(time(0)));

	vector<kv> data(0);

	for (int i = 0;i < num_word; i++) {
		cout << keywords[i] << " : " << counts[i] << endl;
		for (int j = 0; j < counts[i]; j++) {
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
	random_shuffle(ADDdata.begin(), ADDdata.end())
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
	cout << "------------------------" << endl;
	cout << "keywords and counts: " << endl;
	vector<kv> dataset = Zipf(num_keywords, db_size, &MAXCOUNT);
	cout << "maximum response length: " << MAXCOUNT << endl;
	cout << "------------------------" << endl;
	//db_size = dataset.size();
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
  for (auto pair : first4) {
    cout << pair.first << " : " << pair.second << endl;
  }
	int count = 4;
	while (count > 0) {
		cout << "Please input a keyword." << endl;
		string keyword;
		cin >> keyword;
		vector<string> res = client.search(keyword);

		cout << "number of results getting from server: " << res.size() << endl;
		//Remove the dummy entities in raw search results.
		vector<int> inds = client.process(keyword, res);
		cout << "processed search result:" << inds.size() << endl;
    count -= 1;
	}

	for (auto data : ADDdata){
		client.update(data.keyword, data.ind, ADD);
	}

	int count = 4;
	while (count > 0) {
		cout << "Please input a keyword." << endl;
		string keyword;
		cin >> keyword;
		vector<string> res = client.search(keyword);

		cout << "number of results getting from server: " << res.size() << endl;
		//Remove the dummy entities in raw search results.
		vector<int> inds = client.process(keyword, res);
		cout << "processed search result:" << inds.size() << endl;
    count -= 1;
	}

	

	//for (auto ind : inds) {
	//	cout << ind << endl;
	//}

	//Update
  /*vector<kv> update_data = generate_samples(db_size/4-1, &MAXCOUNT);
  vector<int> ids;
  chrono::microseconds threshold(5000);
  chrono::microseconds total(0);
  vector<int> totaltime;
  for (int i = 0; i < 15; i++) {
    kv data  = update_data[i];
    client.update(data.keyword, data.ind, ADD);
  }
  //sleep(5);
  for (int i = 15; i < db_size/4-1; i++) {
    kv data  = update_data[i];
    time_start = chrono::high_resolution_clock::now();
    client.update(data.keyword, data.ind, ADD);
    time_end = chrono::high_resolution_clock::now();
    total += chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    if (i % 16 == 15) {
      if (chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() > threshold.count()){
        cout << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << ", ";
        totaltime.emplace_back(total.count());
        ids.emplace_back(i);
      } 
    }
    
    
  }
  cout << endl ;
  for (auto id:ids) {
    cout << id << ",";
  }
  cout << endl ;
  for (auto t:totaltime) {
    cout << t << ",";
  }*/
	

	//for (int i = 0; i < 500; i++) {
	//	time_start = chrono::high_resolution_clock::now();
	//	client.update("update", i, ADD);
	//	time_end = chrono::high_resolution_clock::now();
	//	cout << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << ", ";
	//}
	//cout << endl;
        //for (int i = 0; i < 8; i++) {
	//	client.update("test", i, DEL);
	//}
	//res.clear();
	//inds.clear();
	//res = client.search("test");
	//inds = client.process("test", res);
	//cout << "processed search result:" << inds.size() << endl;
	//sort(inds.begin(), inds.end());
	////for (auto ind : inds) {
	////	cout << ind << endl;
	////}
	return 0;

}