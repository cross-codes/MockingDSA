#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
i64 nums[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; i++)
      std::cin >> nums[i];

    for (size_t i = 0; i < n - 1; i++) {
      i64 a = nums[i], b = nums[i + 1];
      i64 min = std::min(a, b);
      if (min != 0) {
        if (a == min) {
          nums[i] = 0;
          nums[i + 1] = b - a;
        } else {
          nums[i + 1] = 0;
          nums[i] = a - b;
        }
      }
    }

    bool no = false;
    for (size_t i = 0; i < n - 1; i++) {
      if (nums[i] > nums[i + 1]) {
        std::cout << "NO\n";
        no = true;
        break;
      }
    }

    if (!no)
      std::cout << "YES\n";
  }

  return 0;
}
