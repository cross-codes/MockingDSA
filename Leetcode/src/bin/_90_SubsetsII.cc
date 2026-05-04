#include <algorithm>
#include <set>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums)
  {
    auto subseq =
        [](auto &&subseq,
           const std::vector<int> &vec) -> std::set<std::vector<int>> {
      if (vec.empty())
        return {{}};

      int first = vec[0];
      std::vector<int> rest(vec.begin() + 1, vec.end());
      std::set<std::vector<int>> result{};

      for (auto seq : subseq(subseq, rest))
      {
        std::vector<int> with_first = {first};
        with_first.insert(with_first.end(), seq.begin(), seq.end());

        std::sort(with_first.begin(), with_first.end());
        std::sort(seq.begin(), seq.end());

        result.insert(with_first);
        result.insert(seq);
      }

      return result;
    };

    auto res = subseq(subseq, nums);
    return std::vector<std::vector<int>>(res.begin(), res.end());
  }
};
