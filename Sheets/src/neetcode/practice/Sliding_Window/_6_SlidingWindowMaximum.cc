#include <deque>
#include <vector>

class Solution {
public:
  std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
    std::size_t n = nums.size();
    std::vector<int> res{};

    std::deque<int> deque{};
    for (int i = 0; i < k; i++) {
      while (!deque.empty() && deque.back() < nums[i])
        deque.pop_back();
      deque.push_back(nums[i]);
    }

    res.push_back(deque.front());

    for (std::size_t j = k; j < n; j++) {
      int newVal = nums[j], popVal = nums[j - k];
      while (!deque.empty() && deque.back() < newVal)
        deque.pop_back();
      deque.push_back(newVal);

      if (deque.front() == popVal)
        deque.pop_front();

      res.push_back(deque.front());
    }

    return res;
  }
};
