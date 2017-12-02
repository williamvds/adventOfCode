#define nl '\n'
#include <iostream>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int sum = 0;
  int min, max, cur;

  while (!cin.eof()) {
    cin >> cur;
    min = max = cur;

    while (cin.peek() != '\n' && cin >> cur) {
      if (cur < min) min = cur;
      else if (cur > max) max = cur;
    }

    sum += max -min;
  }

  cout << sum << nl;
  return 0;
}
