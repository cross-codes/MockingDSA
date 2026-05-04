#include <queue>
#include <vector>

class MedianFinder
{
private:
  std::priority_queue<int, std::vector<int>, std::greater<int>> upper_;
  std::priority_queue<int> lower_;

  void balance()
  {
    if (upper_.size() - lower_.size() <= 1)
    {
      int upper_min = upper_.top();
      if (lower_.size() != 0)
      {
        int lower_max = lower_.top();
        if (upper_min < lower_max)
        {
          upper_.pop();
          lower_.pop();
          lower_.push(upper_min);
          upper_.push(lower_max);
          return;
        }
      }
    }
    else
    {
      int upper_min = upper_.top();
      upper_.pop();
      lower_.push(upper_min);
      balance();
    }
  }

public:
  MedianFinder()
  {
  }

  void addNum(int num)
  {
    upper_.push(num);
    balance();
  }

  double findMedian()
  {
    if (upper_.size() + lower_.size() & 1)
      return upper_.top();
    else
      return (lower_.top() + upper_.top()) / 2.0;
  }
};
