// https://adventofcode.com/2017/day/1
#define nl '\n'
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int total = 0;
  vector<char> ls;
  char temp;

  while (cin >> temp)
    ls.push_back(temp);

  for (unsigned i = 0; i < ls.size() /2; ++i) {
    char cur = ls.at(i),
      ahead = ls.at((i +ls.size()/2) % ls.size());
    if (cur == ahead)
      total += (cur -'0') *2;
  }

  cout << total << nl;
  return 0;
}
