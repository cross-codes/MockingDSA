#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q;
  std::cin >> n >> q;

  std::vector<i64> prefix;
  prefix.push_back(0);
  for (int i = 1; i <= n; i++) {
    i64 num;
    std::cin >> num;
    prefix.push_back(prefix[i - 1] + num);
  }

  while (q-- > 0) {
    int a, b;
    std::cin >> a >> b;
    std::cout << prefix[b] - prefix[a - 1] << "\n";
  }

  return 0;
}
