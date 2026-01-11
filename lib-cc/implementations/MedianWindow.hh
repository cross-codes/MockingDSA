#include <set>

class MedianWindow {
 private:
  std::vector<int> array_;
  std::size_t current_begin_, current_end_;
  std::size_t size_, window_size_;
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

    for (std::size_t i = 0; i < size_; i++)
      array_[i] = array[i];

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
      low.erase(low.find(r));
    } else {
      auto it = high.find(r);
      higher_sum -= *it;
      high.erase(high.find(r));
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
