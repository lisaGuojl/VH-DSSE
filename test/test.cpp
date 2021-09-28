#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <chrono>
using namespace std;
int main() {
  chrono::high_resolution_clock::time_point time_start, time_end;
  chrono::microseconds time_diff(1000);
  time_start = chrono::high_resolution_clock::now();
  sleep(1);
  time_end = chrono::high_resolution_clock::now();
  cout << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " microseconds]" << endl;
  cout << time_diff.count() << endl;
  if (chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() > time_diff.count() ){
    cout << "yes" <<endl;
  }
  cout<< (int)time_diff.count() << endl;
  

  return 0;
  
}