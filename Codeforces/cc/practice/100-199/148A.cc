#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _148A {

constexpr int N = static_cast<int>(1e5 + 1);

auto run() -> void {
  std::array<int, 4> nums{};
  for (int i = 0; i < 4; i++)
    std::cin >> nums[i];

  int d;
  std::cin >> d;

  std::array<bool, N> hurt{};

  for (const int &num : nums) {
    for (int i = num; i <= d; i += num)
      hurt[i] = true;
  }

  u32 cnt = 0U;
  for (ssize i = 1Z; i <= d; i++)
    if (hurt[i])
      cnt++;

  std::println("{}", cnt);
}

} // namespace _148A

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

  int t = 1;

  while (t-- > 0)
    _148A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
