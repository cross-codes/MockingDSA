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

namespace _SlidingWindowMedian {

class MedianWindow {
 private:
  std::vector<int> array_;
  std::size_t current_begin_, current_end_;
  std::size_t window_size_;
  std::size_t expected_low_size_, expected_high_size_;

  void balance_sets_() {
    while (low.size() < expected_low_size_) {
      auto it = high.begin();
      low.insert(*it);
      lower_sum += *it;
      higher_sum -= *it;
      high.erase(it);
    }

    while (high.size() < expected_high_size_) {
      auto it = --low.end();
      higher_sum += *it;
      high.insert(*it);
      lower_sum -= *it;
      low.erase(it);
    }
  }

 public:
  std::multiset<int> low, high;
  std::int64_t lower_sum{}, higher_sum{};

  MedianWindow(const std::vector<int>& array, std::size_t k)
      : array_(array), current_begin_(0), current_end_(0), window_size_(k) {
    if (k & 1)
      expected_low_size_ = (k >> 1) + 1, expected_high_size_ = k >> 1;
    else
      expected_low_size_ = expected_high_size_ = k >> 1;

    for (std::size_t i = 0; i < window_size_; i++) {
      low.insert(array_[i]);
      lower_sum += array_[i];
    }

    balance_sets_();
  }

  int next_median() {
    if (current_end_ == 0) [[unlikely]] {
      current_end_ = window_size_;
      return *low.rbegin();
    }

    int r = array_[current_begin_++];

    if (low.contains(r)) {
      auto it = low.find(r);
      lower_sum -= *it;
      low.erase(it);
    } else {
      auto it = high.find(r);
      higher_sum -= *it;
      high.erase(it);
    }

    int e = array_[current_end_++];
    if (!high.empty() && e > *high.begin()) {
      higher_sum += e;
      high.insert(e);
    } else {
      lower_sum += e;
      low.insert(e);
    }

    balance_sets_();
    return *low.rbegin();
  }
};

auto run() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  MedianWindow generator(x, k);
  for (int i = 0; i < n - k + 1; i++) {
    std::cout << generator.next_median() << " ";
  }

  std::cout << "\n";
}

}  // namespace _SlidingWindowMedian

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
    _SlidingWindowMedian::run();

  std::cout.flush();

  return 0;
}
