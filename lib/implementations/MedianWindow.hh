#include <memory>
#include <set>

struct MedianWindow
{
private:
  std::unique_ptr<int[]> array_;
  std::size_t currentBegin_, currentEnd_;
  std::size_t size_, windowSize_;

  std::size_t expectedLowSize_, expectedHighSize_;
  std::multiset<int> low_, high_;

  void balanceSets_()
  {
    while (low_.size() < expectedLowSize_)
    {
      auto it = high_.begin();
      low_.insert(*it);
      high_.erase(it);
    }

    while (high_.size() < expectedHighSize_)
    {
      auto it = --low_.end();
      high_.insert(*it);
      low_.erase(it);
    }
  }

public:
  MedianWindow(std::unique_ptr<int[]> &array, std::size_t arraySize,
               std::size_t windowSize)
      : array_(std::make_unique<int[]>(arraySize)), currentBegin_(0),
        currentEnd_(0), size_(arraySize), windowSize_(windowSize)
  {
    if (windowSize & 1)
      expectedLowSize_  = (windowSize >> 1) + 1,
      expectedHighSize_ = windowSize >> 1;
    else
      expectedLowSize_ = expectedHighSize_ = windowSize >> 1;

    for (std::size_t i = 0; i < size_; i++)
      array_[i] = array[i];

    for (std::size_t i = 0; i < windowSize_; i++)
      low_.insert(array_[i]);

    balanceSets_();
  }

  int nextMedian()
  {
    if (currentEnd_ == 0) [[unlikely]]
    {
      currentEnd_ = windowSize_;
      return *low_.rbegin();
    }

    int r = array_[currentBegin_++];

    if (low_.contains(r))
      low_.erase(low_.find(r));
    else
      high_.erase(high_.find(r));

    int e = array_[currentEnd_++];
    if (!high_.empty() && e > *high_.begin())
      high_.insert(e);
    else
      low_.insert(e);

    balanceSets_();
    return *low_.rbegin();
  }
};
