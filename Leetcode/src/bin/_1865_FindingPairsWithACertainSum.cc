#include <unordered_map>
#include <vector>

class FindSumPairs
{
private:
  std::vector<int> nums1_, nums2_;
  std::unordered_map<int, int> cnt_{};

public:
  FindSumPairs(std::vector<int> &nums1, std::vector<int> &nums2)
  {
    nums1_.resize(nums1.size());
    std::copy(nums1.begin(), nums1.end(), nums1_.begin());

    for (int e : nums2)
    {
      nums2_.push_back(e);
      cnt_[e] += 1;
    }
  }

  void add(int index, int val)
  {
    int old = nums2_[index];
    cnt_[old] -= 1;

    old += val;
    cnt_[old] += 1;

    nums2_[index] = old;
  }

  int count(int tot)
  {
    int cnt{};
    for (int e : nums1_)
      cnt += cnt_[tot - e];

    return cnt;
  }
};
