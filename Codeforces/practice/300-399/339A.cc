#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _339A {

auto run() -> void {
  std::vector<int> operands{};

  int num;
  while (std::cin >> num) {
    operands.push_back(num);
    std::cin.ignore();
  }

  std::ranges::sort(operands);

  for (usize i = 0UZ; i < operands.size() - 1; i++)
    std::print("{}+", operands[i]);

  std::println("{}", operands.back());
}

} // namespace _339A

int main() {
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0)
    _339A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
