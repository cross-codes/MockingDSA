#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>

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

  std::unordered_map<i64, u64> prefixIndices{};
  prefixIndices.reserve(n + 1);
  prefixIndices[0] = 1U;

  std::memset(array.get(), 0x00, sizeof(int) * n);
  std::memset(prefix.get(), 0x00, sizeof(int) * (n + 1));

  u64 cnt = 0ULL;
  for (ssize i = 1; i <= n; i++) {
    std::cin >> array[i - 1];
    prefix[i] = array[i - 1] + prefix[i - 1];

    auto it = prefixIndices.find(prefix[i] - x);
    if (it != prefixIndices.end())
      cnt += it->second;

    prefixIndices[prefix[i]]++;
  }

  std::cout << cnt << "\n";

  return 0;
}
