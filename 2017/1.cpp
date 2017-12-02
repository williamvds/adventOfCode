#define nl '\n'
#include <iostream>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  unsigned int total = 0;
  char first, prev, cur;
  cin >> first;
  prev = first;

  while (cin >> cur) {
    if (prev == cur)
      total += (prev = cur) -'0';

    prev = cur;
  }

  if (cur == first)
    total += cur -'0';

  cout << total << nl;
  return 0;
}
