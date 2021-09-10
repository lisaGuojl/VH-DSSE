#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "cuckoo.h"
using  namespace  std;
using  namespace  cuckoo;

int kukumain() {
	uint8_t* prf_seed = (unsigned char*)"0123456789123456";
	item_type empty_item = make_pair(0, "");
	table_size_type table_size = 512;
	table_size_type stash_size = 0;
	KukuTable table(table_size, stash_size, 50, empty_item, prf_seed);

	string str = "";
	int fail_num = 0;
	for (int i = 0; i < 200; ++i) {
		bool res = table.insert(i+1, str);
		if (res == 0) {
			fail_num += 1;
		}
	}
	cout << fail_num; 
	return 0;
}