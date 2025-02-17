#include <cstdint>
#include <cstring>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;
  if (n == 1U)
    std::cout << "1\n";
  else {
    bool marked[n + 1];
    std::memset(marked, 0, (n + 1) * sizeof(bool));

    u32 numMarked = 0U, ptr = 2, numJumps = 2;
    while (numMarked != n) {
      if (marked[ptr] || numJumps < 2) {
        ptr = (ptr == n) ? 1 : ++ptr;
        numJumps = (marked[ptr]) ? numJumps : ++numJumps;
      } else {
        marked[ptr] = true;
        numMarked++;
        std::cout << ptr << " ";
        ptr = (ptr == n) ? 1 : ++ptr;
        numJumps = (marked[ptr]) ? 0 : 1;
      }
    }

    std::cout << "\n";
  }

  return 0;
}
