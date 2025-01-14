#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>

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

constexpr int _ = 5000;
int arr[_], copy[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  int x;
  std::cin >> n >> x;
  std::unordered_map<int, u32, HasherFunctor> map{};

  for (size_t i = 0U; i < n; i++) {
    int num;
    std::cin >> num;
    arr[i] = copy[i] = num;
  }

  std::sort(&copy[0], &copy[n]);

  bool found = false;
  for (size_t i = 0; i < n; i++) {
    int n1 = copy[i];

    size_t l = i + 1, r = n - 1;
    while (l < r) {
      int n2 = copy[l], n3 = copy[r];
      if (n1 + n2 + n3 > x)
        r--;
      else if (n1 + n2 + n3 < x)
        l++;
      else {
        map[n1]++, map[n2]++, map[n3]++;
        found = true;
        break;
      }
    }

    if (found)
      break;
  }

  if (!found)
    std::cout << "IMPOSSIBLE\n";
  else {
    for (size_t i = 0; i < n; i++) {
      if (map.empty())
        break;

      int currNum = arr[i];

      auto it = map.find(currNum);
      if (it != map.end()) {
        u32 freq = it->second;
        if (freq == 1U)
          map.erase(currNum);
        else
          map[currNum] = --freq;

        std::cout << i + 1U << " ";
      }
    }
  }

  return 0;
}
