#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
  int leastInterval(std::vector<char> &tasks, int n)
  {
    std::array<int, 26> count{};
    for (char task : tasks)
      count[task - 'A']++;

    int max_freq{*std::max_element(count.begin(), count.end())};
    int max_cnt{
        static_cast<int>(std::count(count.begin(), count.end(), max_freq))};

    int time = (max_freq - 1) * (n + 1) + max_cnt;
    return std::max(static_cast<int>(tasks.size()), time);
  }
};
