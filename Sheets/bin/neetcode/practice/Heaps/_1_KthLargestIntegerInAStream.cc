#include <queue>
#include <vector>

class KthLargest {
private:
  std::priority_queue<int, std::vector<int>, std::greater<int>> heap_;
  std::size_t maxSize_ = 0;

public:
  KthLargest(int k, std::vector<int> &nums) : maxSize_(k) {
    for (const int &num : nums)
      add(num);
  }

  int add(int val) {
    if (heap_.size() == maxSize_) {
      int minVal = heap_.top();
      if (minVal < val) {
        heap_.pop();
        heap_.push(val);
      }
    } else
      heap_.push(val);

    return heap_.top();
  }
};
