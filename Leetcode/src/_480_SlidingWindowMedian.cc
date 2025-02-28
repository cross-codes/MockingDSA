#include <set>
#include <vector>

struct MedianWindow {
private:
  std::vector<double> array_;
  std::size_t currentBegin_, currentEnd_;
  std::size_t size_, windowSize_;

  std::size_t expectedLowSize_, expectedHighSize_;
  std::multiset<double> low_, high_;

  void balanceSets_() {
    while (low_.size() < expectedLowSize_) {
      auto it = high_.begin();
      low_.insert(*it);
      high_.erase(it);
    }

    while (high_.size() < expectedHighSize_) {
      auto it = --low_.end();
      high_.insert(*it);
      low_.erase(it);
    }
  }

public:
  MedianWindow(std::vector<int> &array, std::size_t arraySize,
               std::size_t windowSize)
      : array_(), currentBegin_(0), currentEnd_(0), size_(arraySize),
        windowSize_(windowSize) {

    if (windowSize & 1)
      expectedLowSize_ = (windowSize >> 1) + 1,
      expectedHighSize_ = windowSize >> 1;
    else
      expectedLowSize_ = expectedHighSize_ = windowSize >> 1;

    for (std::size_t i = 0; i < size_; i++)
      array_.push_back(array[i]);

    for (std::size_t i = 0; i < windowSize_; i++)
      low_.insert(array_[i]);

    balanceSets_();
  }

  double nextMedian() {
    if (currentEnd_ == 0) [[unlikely]] {
      currentEnd_ = windowSize_;
      if (windowSize_ & 1)
        return *low_.rbegin();
      else
        return (*low_.rbegin() + *high_.begin()) / 2;
    }

    double r = array_[currentBegin_++];

    if (low_.contains(r))
      low_.erase(low_.find(r));
    else
      high_.erase(high_.find(r));

    double e = array_[currentEnd_++];
    if (!high_.empty() && e > *high_.begin())
      high_.insert(e);
    else
      low_.insert(e);

    balanceSets_();
    if (windowSize_ & 1)
      return *low_.rbegin();
    else
      return (*low_.rbegin() + *high_.begin()) / 2;
  }
};

class Solution {
public:
  std::vector<double> medianSlidingWindow(std::vector<int> &nums, int k) {
    std::size_t n = nums.size();
    auto medWin = MedianWindow(nums, n, k);
    std::vector<double> res{};

    for (std::size_t i = 0; i < n - k + 1; i++)
      res.push_back(medWin.nextMedian());

    return res;
  }
};
