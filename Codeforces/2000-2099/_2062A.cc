#include <cstdint>
#include <iostream>
#include <string>

#ifdef CROSS
#include "../../lib/util/Debug.hpp"
#else
#define dbg(...) 249
#endif

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t--) {
    std::string input;
    std::cin >> input;

    u32 cnt = 0U;
    for (char c : input) {
      if (c == '1')
        cnt++;
    }

    std::cout << cnt << "\n";
  }

  return 0;
}
