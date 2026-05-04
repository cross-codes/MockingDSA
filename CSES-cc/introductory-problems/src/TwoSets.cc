#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _TwoSets {

auto run() -> void {
  int n;
  std::cin >> n;

  int mod = n % 4;
  if (mod == 0) {
    std::cout << "YES\n";

    std::vector<int> nums(n);
    for (int i = 1; i <= n; i++) {
      nums[i - 1] = i;
    }
    std::vector<int> set1{}, set2{};
    bool add_to_first{};

    for (size_t i = 0; i < (nums.size() >> 1); i++) {
      if (add_to_first) {
        set1.push_back(nums[i]);
        set1.push_back(nums[nums.size() - i - 1]);
      } else {
        set2.push_back(nums[i]);
        set2.push_back(nums[nums.size() - i - 1]);
      }

      add_to_first = !add_to_first;
    }

    std::cout << set1.size() << "\n";
    for (const int& e : set1) {
      std::cout << e << " ";
    }

    std::cout << "\n" << set2.size() << "\n";

    for (const int& e : set2) {
      std::cout << e << " ";
    }

    std::cout << "\n";
  } else if (mod == 3) {
    std::cout << "YES\n";
    int m = (1 + n) >> 2;

    std::vector<int> nums(n - 3);
    for (int i = 1, idx = 0; i <= n; i++) {
      if (i != m && i != (m << 1) && i != (m << 1) + m) [[unlikely]] {
        nums[idx] = i;
        idx += 1;
      }
    }
    std::vector<int> set1{}, set2{};
    set1.push_back(m);
    set1.push_back(m << 1);
    set2.push_back((m << 1) + m);

    bool add_to_first{};
    for (size_t i = 0; i < (nums.size() >> 1); i++) {
      if (add_to_first) {
        set1.push_back(nums[i]);
        set1.push_back(nums[nums.size() - i - 1]);
      } else {
        set2.push_back(nums[i]);
        set2.push_back(nums[nums.size() - i - 1]);
      }

      add_to_first = !add_to_first;
    }

    std::cout << set1.size() << "\n";
    for (const int& e : set1) {
      std::cout << e << " ";
    }

    std::cout << "\n" << set2.size() << "\n";

    for (const int& e : set2) {
      std::cout << e << " ";
    }

    std::cout << "\n";
  } else {
    std::cout << "NO\n";
  }
}

}  // namespace _TwoSets

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _TwoSets::run();

  std::cout.flush();

  return 0;
}
