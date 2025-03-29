#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _2064C {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::unique_ptr<int[]> a(new int[n]);
  for (ssize i = 0Z; i < n; i++)
    std::cin >> a[i];

  std::unique_ptr<i64[]> prefix(new i64[n]), suffix(new i64[n]);
  std::memset(prefix.get(), 0x00, sizeof(i64) * n);
  std::memset(suffix.get(), 0x00, sizeof(i64) * n);

  if (a[0] > 0)
    prefix[0] = a[0];

  for (ssize i = 1Z; i < n; i++) {
    prefix[i] = prefix[i - 1];
    if (a[i] > 0)
      prefix[i] += a[i];
  }

  if (a[n - 1] < 0)
    suffix[n - 1] = -a[n - 1];

  for (ssize i = n - 2; i >= 0; i--) {
    suffix[i] = suffix[i + 1];
    if (a[i] < 0)
      suffix[i] += -a[i];
  }

  i64 ans = 0LL;
  for (ssize i = 0Z; i < n; i++)
    ans = std::max(ans, prefix[i] + suffix[i]);

  std::println("{}", ans);
}

} // namespace _2064C

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
  std::cin >> t;

  while (t-- > 0)
    _2064C::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
