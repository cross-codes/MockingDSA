#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string input;
  std::cin >> input;

  size_t n = input.size();
  std::string forward, backward, oddComp;
  forward.reserve(n), backward.reserve(n), oddComp.reserve(n);

  std::array<int, 26> freq = {};
  for (const char &c : input)
    freq[c - 'A']++;

  int oddFreq = 0;
  for (const int &f : freq)
    if ((f & 1) != 0)
      oddFreq++;

  if (oddFreq >= 2 || (oddFreq == 1 && (n & 1) == 0))
    backward = "NO SOLUTION\n";
  else {
    bool inv = false;
    char odd = '\u001F';
    int oddIdx = -1;
    for (int i = 0; i < 26; i++) {
      char c = static_cast<char>('A' + i);
      if ((freq[i] & 1) != 0) {
        odd = c;
        oddIdx = i;
        continue;
      } else {
        for (int j = 0; j < freq[i]; j++) {
          if (inv)
            forward += c;
          else
            backward += c;
          inv = !inv;
        }
      }
    }

    std::reverse(backward.begin(), backward.end());

    if (oddFreq == 1) {
      for (int i = 0; i < freq[oddIdx]; i++)
        oddComp += odd;
      backward += oddComp + forward + "\n";
    } else
      backward += forward + "\n";
  }

  std::cout << backward;

  return 0;
}
