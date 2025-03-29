#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _165A {

auto hasRN(std::pair<int, int>, const std::unique_ptr<std::pair<int, int>[]> &,
           usize) -> bool;
auto hasLN(std::pair<int, int>, const std::unique_ptr<std::pair<int, int>[]> &,
           usize) -> bool;
auto hasLoN(std::pair<int, int>, const std::unique_ptr<std::pair<int, int>[]> &,
            usize) -> bool;
auto hasUpN(std::pair<int, int>, const std::unique_ptr<std::pair<int, int>[]> &,
            usize) -> bool;

auto run() -> void {
  usize n;
  std::cin >> n;

  std::unique_ptr<std::pair<int, int>[]> points(new std::pair<int, int>[n]);
  for (usize i = 0UZ; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    points[i] = {x, y};
  }

  u32 cnt = 0U;
  for (usize i = 0UZ; i < n; i++) {
    auto point = points[i];
    if (hasRN(point, points, n) && hasLN(point, points, n) &&
        hasLoN(point, points, n) && hasUpN(point, points, n))
      cnt++;
  }

  std::println("{}", cnt);
}

auto hasRN(std::pair<int, int> point,
           const std::unique_ptr<std::pair<int, int>[]> &points, usize n)
    -> bool {
  for (usize i = 0UZ; i < n; i++) {
    auto &[x, y] = points[i];
    if (x > point.first && y == point.second) return true;
  }

  return false;
}

auto hasLN(std::pair<int, int> point,
           const std::unique_ptr<std::pair<int, int>[]> &points, usize n)
    -> bool {
  for (usize i = 0UZ; i < n; i++) {
    auto &[x, y] = points[i];
    if (x < point.first && y == point.second) return true;
  }

  return false;
}

auto hasLoN(std::pair<int, int> point,
            const std::unique_ptr<std::pair<int, int>[]> &points, usize n)
    -> bool {
  for (usize i = 0UZ; i < n; i++) {
    auto &[x, y] = points[i];
    if (x == point.first && y > point.second) return true;
  }

  return false;
}

auto hasUpN(std::pair<int, int> point,
            const std::unique_ptr<std::pair<int, int>[]> &points, usize n)
    -> bool {
  for (usize i = 0UZ; i < n; i++) {
    auto &[x, y] = points[i];
    if (x == point.first && y < point.second) return true;
  }

  return false;
}

}  // namespace _165A

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

  while (t-- > 0) _165A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
