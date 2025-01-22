#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <chrono>
#include <cstdint>
#include <iostream>
#include <set>
#include <unordered_set>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

struct HasherFunctor {

private:
  static uint64_t randomAddress() {
    char *p = new char;
    delete p;
    return uint64_t(p);
  }

  static uint32_t hash32(uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> uint64_t operator()(T x) const {
    static const uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n;
    int k;
    std::cin >> n >> k;

    std::multiset<int> nums{};
    for (size_t i = 0; i < n; i++) {
      int num;
      std::cin >> num;
      nums.insert(num);
    }

    std::unordered_set<int, ::HasherFunctor> match{};

    for (int elem : nums) {
      if (nums.find(k - elem) != nums.end()) {
        if (k == elem << 1) {
          if (nums.count(elem) > 1)
            match.insert(elem);
          else
            continue;
        } else
          match.insert(elem);
      }
    }

    u32 score = 0U;
    while (!nums.empty()) {
      auto aliceIt = std::prev(nums.end());
      while (aliceIt != nums.begin() && match.contains(*aliceIt))
        aliceIt = std::prev(aliceIt);

      int alice = *(aliceIt);
      if (k != alice << 1) {
        if (nums.count(alice) == 1)
          match.erase(alice);

        nums.erase(aliceIt);

        auto it = nums.find(k - alice);

        if (it != nums.end()) {
          score++;
          size_t cnt = nums.count(k - alice);
          if (cnt == 1)
            match.erase(k - alice);

          nums.erase(it);
        } else {
          auto curit = std::prev(nums.end());
          while (curit != nums.begin() && match.contains(*curit))
            curit = std::prev(curit);

          if (nums.count(*curit) == 1)
            match.erase(*curit);
          nums.erase(curit);
        }
      } else {
        if (nums.count(alice) == 1)
          match.erase(alice);

        nums.erase(aliceIt);

        auto it = nums.find(k - alice);

        if (it != nums.end()) {
          score++;
          size_t cnt = nums.count(k - alice);
          if (cnt <= 2)
            match.erase(k - alice);

          nums.erase(it);
        } else {
          auto curit = std::prev(nums.end());
          while (curit != nums.begin() && match.contains(*curit))
            curit = std::prev(curit);

          size_t cnt = nums.count(*curit);
          if (*curit == k >> 1) {
            auto copt = curit;
            curit = nums.upper_bound(*curit);
            if (curit == nums.end()) {
              curit = nums.lower_bound(*curit - 1);
              if (nums.count(*curit) == 1)
                match.erase(*curit);
              nums.erase(*curit);
            }
          } else {
            if (cnt == 1)
              match.erase(*curit);
            nums.erase(curit);
          }
        }
      }
    }

    std::cout << score << "\n";
  }

  return 0;
}
