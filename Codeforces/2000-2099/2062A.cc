#include <cstdint>
#include <cstring>
#include <iostream>
#include <print>
#include <sys/types.h>

#ifdef CROSS
#include "util/Debug.hh"
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

  while (t-- > 0) {
    std::string input;
    std::cin >> input;

    int cnt = 0;
    for (char c : input) {
      if (c == '1')
        cnt++;
    }

    std::println("{0}", cnt);
  }

  return 0;
}
