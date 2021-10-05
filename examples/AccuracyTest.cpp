
#include <iostream>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
#include <unordered_set>
#include "examples.h"
using namespace std;

vector<pair<string, int>> first4ini = {};
vector<kv> SETUPdata(0);
vector<kv> ADDdata(0);
vector<kv> DELdata(0);

std::string random_string_a(std::size_t length)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	static std::default_random_engine rng(std::time(nullptr));
	static std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

	std::string str;
	while (str.size() < length) str += alphabet[distribution(rng)];
	return str;
}

vector<kv> Zipf(int num_word, int size, int* p) {
	float sum = 0.0;
	for (int i = 1; i <= num_word; i++) {
		sum += 1.0 / i;
	}

	vector<string> keywords = { "test", "sse", "dynamic", "static" };
	for (int i = 4; i < num_word; i++) {
		string keyword = random_string_a(5);
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

	vector<kv> data(0);

	for (int i = 0;i < num_word; i++) {
		cout << keywords[i] << " : " << counts[i] << endl;
		for (int j = 0; j < counts[i]; j++) {
			kv sample;
			sample.keyword = keywords[i];
			sample.ind = j;
			sample.op = ADD;
			string id = std::to_string(j);

			data.emplace_back(sample);

		}
	}

	random_shuffle(data.begin(), data.end());
	return data;
}

vector<string> compute_union(vector<string> v1, vector<string> v2) {
	vector<unsigned long long> vec1;
	vector<unsigned long long> vec2;
	vector<unsigned long long> uset;
	vector<string> res;
	for (auto i : v1) {
		unsigned long long num = stoull(i, nullptr, 0);
		vec1.emplace_back(num);
	}
	for (auto i : v2) {
		vec2.emplace_back(stoull(i, nullptr, 0));
	}
	sort(vec1.begin(), vec1.end());
	vec1.erase(unique(vec1.begin(), vec1.end()), vec1.end());
	sort(vec2.begin(), vec2.end());
	vec2.erase(unique(vec2.begin(), vec2.end()), vec2.end());
	set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::inserter(uset, uset.begin()));
	for (auto i : uset) {
		res.emplace_back(to_string(i));
	}
	return res;
}

int AccuracyTest() {

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
	if (MAXCOUNT > (int) 1 << 16 - 1){
		cout << "maximum response length should less than 2^16-1, Please try smaller N." << endl;
		throw "MRL is too larger.";
	}
	db_size = SETUPdata.size();
	cout << "setup database size: " << db_size << endl;
 	MAXCOUNT = 0;

	Client* client1 = new Client(db_size, alpha, MAXCOUNT);
	Client* client2 = new Client(db_size, alpha, MAXCOUNT);
	Client* client3 = new Client(db_size, alpha, MAXCOUNT);

	//Setup
	float addfn[3][4][5] = {};
	float delfn[3][4][5] = {};
	float delfp[3][4][5] = {};
	for (int l = 0; l < 10; l++)
	{
		cout << l+1 << "-th run" <<endl;
    	client1->setup(SETUPdata);
		client2->setup(SETUPdata);
		client3->setup(SETUPdata);
    	vector<pair<string, int>> first4(first4ini.begin(), first4ini.end());

		for (auto pair : first4) {
			cout << pair.first << " : " << pair.second << endl;
		}

		cout << "------------------------" << endl;
		int addsize = floor(ADDdata.size() / 5);
		vector<vector<int>> additems;
		additems.resize(4);
		for (int ai = 0; ai < 5; ai++) {
			cout << "ADD " << ai+1 << "0% entities" << endl;
			vector<kv> adata;
			if (ai == 4) {
				adata.assign(ADDdata.begin() + ai * addsize, ADDdata.end());
			}
			else {
				adata.assign(ADDdata.begin() + ai * addsize, ADDdata.begin() + (ai + 1) * addsize);
			}
			for (auto data : adata) {
				client1->update(data.keyword, data.ind, ADD);
				client2->update(data.keyword, data.ind, ADD);
				client3->update(data.keyword, data.ind, ADD);
				if (data.keyword == "test") {
					first4[0].second += 1;
				}
				if (data.keyword == "sse") {
					first4[1].second += 1;
				}
				if (data.keyword == "dynamic") {
					first4[2].second += 1;
				}
				if (data.keyword == "static") {
					first4[3].second += 1;
				}
			}
			db_size += adata.size();
			cout << "Update " << adata.size() << " items" << endl;
      		for(auto pair : first4) {
        		cout << pair.second << ", " <<endl;
      		}
			int count = 0;
			while (count < 4) {
				cout << "Search " << first4[count].first << endl;
				vector<string> res1 = client1->search(first4[count].first);
				vector<int> inds1 = client1->process(first4[count].first, res1);
				addfn[0][count][ai] += 100.0 * (first4[count].second - inds1.size()) / first4[count].second;
				vector<string> res2 = client2->search(first4[count].first);
				vector<string> union2 = compute_union(res1, res2);
				//cout << union2.size() << endl;
				vector<int> inds2 = client2->process(first4[count].first, union2);

				//cout << "k = 2 " << endl;
				//cout << "processed search result:" << inds2.size() << endl;
				//cout << "FN rate: " << 100.0 * (first4[count].second - inds2.size()) / first4[count].second << "%" << endl;
				addfn[1][count][ai] += 100.0 * (first4[count].second - inds2.size()) / first4[count].second;

				vector<string> res3 = client3->search(first4[count].first);
				vector<string> union3 = compute_union(union2, res3);
				vector<int> inds3 = client3->process(first4[count].first, union3);

				//cout << "k = 3 " << endl;
				//cout << "processed search result:" << inds3.size() << endl;
				//cout << "FN rate: " << 100.0 * (first4[count].second - inds3.size()) / first4[count].second << "%" << endl;
				addfn[2][count][ai] += 100.0 * (first4[count].second - inds3.size()) / first4[count].second;
				count += 1;
			}


		}
		cout << "------------------------" << endl;
		int delsize = floor(DELdata.size() / 5);
		vector<vector<int>> delitems={};
		delitems.resize(4);
		for (int di = 0; di < 5;di++) {
			cout << "DEL " << di+1 << "0% entities" << endl;
			vector<kv> ddata;
			int sum = 0;
			if (di == 4) {
				ddata.assign(DELdata.begin() + di * delsize, DELdata.end());
			}
			else {
				ddata.assign(DELdata.begin() + di * delsize, DELdata.begin() + (di + 1) * delsize);
			}

			for (auto data : ddata) {
				client1->update(data.keyword, data.ind, DEL);
				client2->update(data.keyword, data.ind, DEL);
				client3->update(data.keyword, data.ind, DEL);
				if (data.keyword == "test") {
					delitems[0].emplace_back(data.ind);
				}
				if (data.keyword == "sse") {
					delitems[1].emplace_back(data.ind);
				}
				if (data.keyword == "dynamic") {
					delitems[2].emplace_back(data.ind);
				}
				if (data.keyword == "static") {
					delitems[3].emplace_back(data.ind);
				}
				sum += 1;
			}
			for (auto i : delitems) {
				cout << i.size() << ", ";
				sort(i.begin(), i.end());
			}
			cout << " DEL " << sum << " items" << endl;

			int count = 0;
			while (count < 4) {
				vector<int> total={};
				vector<int> real={};
				vector<int> fp={};
				for (int i = 0; i < first4[count].second; i++) {
					total.emplace_back(i);
				}
				sort(delitems[count].begin(), delitems[count].end());
				std::set_difference(total.begin(), total.end(), delitems[count].begin(), delitems[count].end(),
					std::inserter(real, real.begin()));
				//cout << "number of real results should be returned: " << real.size() << endl;

				//cout << "k = 1" << endl;
				vector<string> res1 = client1->search(first4[count].first);
				vector<int> inds1 = client1->process(first4[count].first, res1);
				//cout << "returned search result:" << inds1.size() << endl;
				unordered_set<int> s(inds1.begin(), inds1.end());
				int fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s.find(k) != s.end();});
				//cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;
				int tp_num = count_if(real.begin(), real.end(), [&](int k) {return s.find(k) != s.end();});
				//cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;
				delfn[0][count][di] += 100.0 * (real.size() - tp_num) / real.size();
				delfp[0][count][di] += 100.0 * fp_num / real.size();

				//cout << "k = 2" << endl;
				vector<string> res2 = client2->search(first4[count].first);
				vector<string> union2 = compute_union(res1, res2);
				vector<int> inds2 = client2->process(first4[count].first, union2);
				unordered_set<int> s2(inds2.begin(), inds2.end());
				fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s2.find(k) != s2.end();});
				//cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;
				tp_num = count_if(real.begin(), real.end(), [&](int k) {return s2.find(k) != s2.end();});
				//cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;
				delfn[1][count][di] += 100.0 * (real.size() - tp_num) / real.size();
				delfp[1][count][di] += 100.0 * fp_num / real.size();

				//cout << "k = 3" << endl;
				vector<string> res3 = client3->search(first4[count].first);
				vector<string> union3 = compute_union(union2, res3);
				vector<int> inds3 = client3->process(first4[count].first, union3);

				unordered_set<int> s3(inds3.begin(), inds3.end());
				fp_num = count_if(delitems[count].begin(), delitems[count].end(), [&](int k) {return s3.find(k) != s3.end();});
				//cout << "FP num: " << fp_num << ", rate: " << 100.0 * fp_num / real.size() << "%" << endl;
				tp_num = count_if(real.begin(), real.end(), [&](int k) {return s3.find(k) != s3.end();});
				//cout << "FN num: " << real.size() - tp_num << ", rate: " << 100.0 * (real.size() - tp_num) / real.size() << "%" << endl;
				delfn[2][count][di] += 100.0 * (real.size() - tp_num) / real.size();
				delfp[2][count][di] += 100.0 * fp_num / real.size();



				count++;
			}
			
		}
    delete client1;
    delete client2;
		delete client3;
		db_size = SETUPdata.size();
		client1 = new Client(db_size, alpha, MAXCOUNT);
		client2 = new Client(db_size, alpha, MAXCOUNT);
		client3 = new Client(db_size, alpha, MAXCOUNT);

	}



	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 3; i++) {

				cout << "ADD " << 10 * (k + 1) << ": " << " k=" << i + 1 << ", " << j + 1 << "-th:  accfn: " << addfn[i][j][k] / 10 << endl;

			}
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 3; i++) {

				cout << "DEL " << 10 * (k + 1) << ": " << "k=" << i + 1 << ", " << j + 1 << "-th:  delfn: " << delfn[i][j][k] / 10 << endl;
				cout << "DEL " << 10 * (k + 1) << ": " << "k=" << i + 1 << ", " << j + 1 << "-th:  delfp: " << delfp[i][j][k] / 10 << endl;
			}
		}
	}

	return 0;

}
