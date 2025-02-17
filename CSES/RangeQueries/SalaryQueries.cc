#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

void qsort(int **, std::size_t, std::size_t);
inline void swap(int **, std::size_t, std::size_t);
inline int get(int *, std::size_t);
inline void add(int *, std::size_t, int);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  return 0;
}
