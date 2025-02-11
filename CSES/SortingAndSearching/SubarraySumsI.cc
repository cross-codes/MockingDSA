#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_set>

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ssize n;
  i64 x;
  std::cin >> n >> x;

  std::unique_ptr<int[]> array(new int[n]);
  std::unique_ptr<i64[]> prefix(new i64[n + 1]);

  std::unordered_set<i64> prefixIndices{};
  prefixIndices.reserve(n + 1), prefixIndices.insert(0U);

  std::memset(array.get(), 0x00, sizeof(int) * n);
  std::memset(prefix.get(), 0x00, sizeof(int) * (n + 1));

  u64 cnt = 0ULL;
  for (ssize i = 1; i <= n; i++) {
    std::cin >> array[i - 1];
    prefix[i] = array[i - 1] + prefix[i - 1];

    if (prefixIndices.contains(prefix[i] - x))
      cnt++;

    prefixIndices.insert(prefix[i]);
  }

  std::cout << cnt << "\n";

  return 0;
}
