#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n, m;
    std::cin >> n >> m;

    std::vector<int> permutation(n, 0);

    bool bad = false;

    for (size_t i = 0; i < n; i++) {
      std::vector<int> row{};

      for (size_t j = 0; j < m; j++) {
        int card;
        std::cin >> card;
        row.push_back(card);
      }

      std::sort(row.begin(), row.end());
      int element = row[0];
      if (element < static_cast<int>(n))
        permutation[element] = static_cast<int>(i + 1);
      else
        bad = true;

      if (!bad) {
        for (size_t j = 1; j < m; j++) {
          if (row[j] - row[j - 1] != static_cast<int>(n)) {
            bad = true;
            break;
          }
        }
      }
    }

    if (!bad) {
      for (auto elem : permutation)
        std::cout << elem << " ";

      std::cout << "\n";
    } else
      std::cout << "-1\n";
  }

  return 0;
}
