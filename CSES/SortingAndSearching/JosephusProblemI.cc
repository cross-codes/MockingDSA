#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _JosephusProblemI {

auto run() -> void {
  u32 n;
  std::cin >> n;
  if (n == 1U) {
    std::cout << "1\n";
  } else {
    std::unique_ptr<int[]> marked(new int[n + 1]);
    std::memset(marked.get(), 0, (n + 1) * sizeof(bool));

    u32 numMarked = 0U, ptr = 2, numJumps = 2;
    while (numMarked != n) {
      if (marked[ptr] || numJumps < 2) {
        ptr      = (ptr == n) ? 1 : ++ptr;
        numJumps = (marked[ptr]) ? numJumps : ++numJumps;
      } else {
        marked[ptr] = true;
        numMarked++;
        std::cout << ptr << " ";
        ptr      = (ptr == n) ? 1 : ++ptr;
        numJumps = (marked[ptr]) ? 0 : 1;
      }
    }

    std::cout << "\n";
  }
}

}  // namespace _JosephusProblemI

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};
  std::cin >> t;

  while (t-- > 0) _JosephusProblemI::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
