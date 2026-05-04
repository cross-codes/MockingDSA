#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

class Solution
{
private:
  auto lb(int idx, const std::vector<std::vector<int>> &sorted_intervals) -> int
  {
    int n{static_cast<int>(sorted_intervals.size())};
    int l{idx - 1}, r{n}, target{sorted_intervals[idx][1]};

    auto predicate = [&sorted_intervals, &target](int i) {
      return target < sorted_intervals[i][0];
    };

    while (r - l > 1)
    {
      int m{std::midpoint(l, r)};
      (predicate(m) ? r : l) = m;
    }

    if (l == -1)
      return -1;

    if (l == n - 1)
      return (sorted_intervals[l][0] == target) ? l : -1;

    return (sorted_intervals[l][0] == target) ? l : r;
  }

public:
  std::vector<int> findRightInterval(std::vector<std::vector<int>> &intervals)
  {
    int n{static_cast<int>(intervals.size())};
    std::unordered_map<int, int> interval_idx{};
    std::vector<int> res(n, -1);

    for (int i = 0; i < n; i++)
      interval_idx[intervals[i][0]] = i;

    auto SORTING_ORDER = [](const std::vector<int> &A,
                            const std::vector<int> &B) { return A[0] < B[0]; };

    std::sort(intervals.begin(), intervals.end(), SORTING_ORDER);

    for (int i = 0; i < n; i++)
    {
      const auto &interval = intervals[i];
      int new_idx          = lb(i, intervals);
      if (new_idx == -1)
        res[interval_idx[interval[0]]] = -1;
      else
      {
        const auto &new_interval       = intervals[new_idx];
        res[interval_idx[interval[0]]] = interval_idx[new_interval[0]];
      }
    }

    return res;
  }
};
