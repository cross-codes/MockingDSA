#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _141A {

auto run() -> void {
  std::array<int, 26> freq{};

  std::string guest, host, mess;
  std::cin >> guest >> host >> mess;

  auto update = [&](const char &c) { freq[c - 'A']++; };

  std::ranges::for_each(guest, update);
  std::ranges::for_each(host, update);
  std::ranges::for_each(mess, [&](const char &c) { freq[c - 'A']--; });

  for (auto &f : freq) {
    if (f != 0) {
      std::println("NO");
      return;
    }
  }

  std::println("YES");
}

} // namespace _141A

int main() {
#ifdef ANTUMBRA
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

  while (t-- > 0)
    _141A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
