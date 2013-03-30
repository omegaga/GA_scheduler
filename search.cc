#include <iostream>
#include <vector>
using namespace std;
int size_ = 5;
int search(vector<double>& roulette, double shuf) {
  int left = 0, right = size_;
  while ( left <= right ) {
    int mid = (left + right) / 2;
    if (roulette[mid] == shuf) return mid;
    else
      if (roulette[mid] > shuf) right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}


int main() {
  vector<double> roulette(5);
  roulette[0]=0.2;
  roulette[1]=0.4;
  roulette[2]=0.6;
  roulette[3]=0.8;
  roulette[4]=1.0;
  cout << search(roulette, 0.9);
}
