#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <chrono>
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

namespace _SlidingWindowMode {

struct HasherFunctor {
 private:
  static std::uint64_t randomAddress() {
    char* p = new char;
    delete p;
    return std::uint64_t(p);
  }

  static std::uint32_t hash32(std::uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static std::uint64_t splitmix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

 public:
  template <typename T>
  std::uint64_t operator()(T x) const {
    static const std::uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

auto run() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  std::map<int, std::set<int>> inverse_mapping{};
  std::unordered_map<int, int, HasherFunctor> freq{};
  freq.reserve(n);

  auto add_element = [&](int e) -> void {
    int prev = freq[e];
    freq[e] += 1;

    if (inverse_mapping.contains(prev)) {
      auto& set = inverse_mapping[prev];
      set.erase(e);
      if (set.size() == 0) {
        inverse_mapping.erase(prev);
      }
    }

    inverse_mapping[prev + 1].insert(e);
  };

  auto remove_element = [&](int e) -> void {
    int curr = freq[e];
    freq[e] -= 1;
    if (freq[e] == 0) {
      freq.erase(e);
    }

    auto& set = inverse_mapping[curr];
    set.erase(e);
    if (set.size() == 0) {
      inverse_mapping.erase(curr);
    }

    if (curr > 1) {
      inverse_mapping[curr - 1].insert(e);
    }
  };

  for (int i = 0; i < k; i++) {
    add_element(x[i]);
  }

  std::cout << *inverse_mapping.rbegin()->second.begin() << " ";

  for (int i = k; i < n; i++) {
    remove_element(x[i - k]);
    add_element(x[i]);

    std::cout << *inverse_mapping.rbegin()->second.begin() << " ";
  }

  std::cout << "\n";
}

}  // namespace _SlidingWindowMode

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
    _SlidingWindowMode::run();

  std::cout.flush();

  return 0;
}
