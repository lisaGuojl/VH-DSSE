
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
#include <unordered_set>
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

int myrandom(int i) { return std::rand() % i; }


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
		//cout << keywords[i] << " : " << counts[i] << endl;
		for (int j = 0; j < counts[i]; j++) {
			kv sample;
			sample.keyword = keywords[i];
			sample.ind = j;
			sample.op = ADD;
			string id = std::to_string(j);
			
			if (j > floor(counts[i] * 0.95)) {
				ADDdata.emplace_back(sample);
			}
			else {
				data.emplace_back(sample);
			}
		}
	}

	random_shuffle(data.begin(), data.end());
	random_shuffle(ADDdata.begin(), ADDdata.end());
	return data;
}

vector<string> compute_union(vector<string> v1, vector<string> v2) {
	vector<unsigned long long> vec1;
	vector<unsigned long long> vec2;
	vector<unsigned long long> uset;
	vector<string> res;
	for(auto i : v1) {
		unsigned long long num = stoull(i,nullptr,0);
		vec1.emplace_back(num);
	}
	for(auto i : v2) {
		vec2.emplace_back(stoull(i,nullptr,0));
	}
	sort(vec1.begin(),vec1.end());
	vec1.erase(unique(vec1.begin(), vec1.end()), vec1.end());
	sort(vec2.begin(),vec2.end());
	vec2.erase(unique(vec2.begin(), vec2.end()), vec2.end());
	set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::inserter(uset, uset.begin()));
	for (auto i : uset) {
		res.emplace_back(to_string(i));
	}
	return res;
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
	db_size = dataset.size();
	cout << "setup database size: " << db_size << endl;
	Client client1(db_size, alpha, MAXCOUNT);
	Client client2(db_size, alpha, MAXCOUNT);
	Client client3(db_size, alpha, MAXCOUNT);


	//Setup
	client1.setup(dataset);
	client2.setup(dataset);
	client3.setup(dataset);



	//Search
	for (auto pair : first4) {
		cout << pair.first << " : " << pair.second << " (" << floor(pair.second * 0.95) << ")" << endl;
	}
	int count = 0;
	while (count < 4) {
		/*cout << "Please input a keyword." << endl;
		string keyword;
		cin >> keyword;*/
		vector<string> res = client1.search(first4[count].first);

		cout << "number of results getting from server: " << res.size() << endl;
		//Remove the dummy entities in raw search results.
		vector<int> inds = client1.process(first4[count].first, res);
		cout << "processed search result:" << inds.size() << endl;
		count += 1;
	}
	cout << "Search done" << endl;
 cout << "------------------------" << endl;
	for (auto data : ADDdata) {
		client1.update(data.keyword, data.ind, ADD);
		client2.update(data.keyword, data.ind, ADD);
		client3.update(data.keyword, data.ind, ADD);
	}
	db_size += ADDdata.size();
	cout << "Update " << ADDdata.size() << " items" << endl;
	count = 0;

	while (count < 4) {
		cout << "\n" << "Search " << first4[count].first << endl;
		vector<string> res1 = client1.search(first4[count].first);

		cout << "number of results getting from server: " << res1.size() << endl;
		//Remove the dummy entities in raw search results.
		vector<int> inds1 = client1.process(first4[count].first, res1);
		cout << "k = 1 " << endl;
		cout << "processed search result:" << inds1.size() << endl;
		cout << "FN rate: " << 100.0 * (first4[count].second - inds1.size()) / first4[count].second << "%" << endl;
		
		vector<string> res2 = client2.search(first4[count].first);
		vector<string> union2 = compute_union(res1, res2);
		cout << union2.size() << endl;
		vector<int> inds2 = client2.process(first4[count].first, union2);

		cout << "k = 2 " << endl;
		cout << "processed search result:" << inds2.size() << endl;
		cout << "FN rate: " << 100.0 * (first4[count].second - inds2.size()) / first4[count].second << "%" << endl;
		
		vector<string> res3 = client3.search(first4[count].first);
		vector<string> union3 = compute_union(union2, res3);
		vector<int> inds3 = client3.process(first4[count].first, union3);

		cout  << "k = 3 " << endl;
		cout << "processed search result:" << inds3.size() << endl;
		cout << "FN rate: " << 100.0 * (first4[count].second - inds3.size()) / first4[count].second << "%" << endl;
		

		count += 1;
	}
  cout << "------------------------" << endl;

	dataset.insert(dataset.end(), ADDdata.begin(), ADDdata.end());
	vector<vector<int>> delitems;
	delitems.resize(4);
	int sum = 0;
	for (int i = 0; i < dataset.size(); i++) {
		if (i % 10 == 1) {
			client1.update(dataset[i].keyword, dataset[i].ind, DEL);
			client2.update(dataset[i].keyword, dataset[i].ind, DEL);
			client3.update(dataset[i].keyword, dataset[i].ind, DEL);
			if (dataset[i].keyword == "test") {
				delitems[0].emplace_back(dataset[i].ind);
			}
			if (dataset[i].keyword == "sse") {
				delitems[1].emplace_back(dataset[i].ind);
			}
			if (dataset[i].keyword == "dynamic") {
				delitems[2].emplace_back(dataset[i].ind);
			}
			if (dataset[i].keyword == "static") {
				delitems[3].emplace_back(dataset[i].ind);
			}
			sum += 1;
		}

	}
	for (auto i : delitems) {
		cout << i.size() << ", ";
		sort(i.begin(), i.end());
	}
	
	cout << " DEL " << sum << " items" << endl;
	count = 0;
	while (count < 4) {
		cout << "\n" << "Search " << first4[count].first << endl;
		/*cout << "Please input a keyword." << endl;
		string keyword;
		cin >> keyword;*/
		vector<int> total;
		vector<int> real;
		vector<int> fp;
		for (int i = 0; i < first4[count].second; i++) {
			total.emplace_back(i);
		}
		sort(delitems[count].begin(), delitems[count].end());
		std::set_difference(total.begin(), total.end(), delitems[count].begin(), delitems[count].end(),
			std::inserter(real, real.begin()));
		cout << "number of real results should be returned: " << real.size() << endl;

		cout << "k = 1" <<endl;
		vector<string> res1 = client1.search(first4[count].first);
		vector<int> inds1 = client1.process(first4[count].first, res1);
		cout << "returned search result:" << inds1.size() << endl;
		unordered_set<int> s(inds1.begin(), inds1.end());
		int fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s.find(k) != s.end();});
		cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;

		int tp_num = count_if(real.begin(), real.end(), [&](int k) {return s.find(k) != s.end();});
		cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;

		cout << "k = 2" <<endl;
		vector<string> res2 = client2.search(first4[count].first);
		vector<string> union2 = compute_union(res1, res2);
		vector<int> inds2 = client2.process(first4[count].first, union2);
		unordered_set<int> s2(inds2.begin(), inds2.end());
		fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s2.find(k) != s2.end();});
		cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;
		tp_num = count_if(real.begin(), real.end(), [&](int k) {return s2.find(k) != s2.end();});
		cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;

		cout << "k = 3" <<endl;
		vector<string> res3 = client3.search(first4[count].first);
		vector<string> union3 = compute_union(union2, res3);
		vector<int> inds3 = client3.process(first4[count].first, union3);

		unordered_set<int> s3(inds3.begin(), inds3.end());
		fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s3.find(k) != s3.end();});
		cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;
		tp_num = count_if(real.begin(), real.end(), [&](int k) {return s3.find(k) != s3.end();});
		cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;


		count += 1;
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
