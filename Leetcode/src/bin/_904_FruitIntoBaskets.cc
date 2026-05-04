#include <climits>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int totalFruit(std::vector<int> &fruits)
  {
    int n = static_cast<int>(fruits.size());

    std::unordered_map<int, int> seen{}; // fruit -> idx
    int l{}, r{}, mx{INT_MIN};
    while (r < n)
    {
      if (seen.size() == 2 && !seen.contains(fruits[r]))
      {
        mx = std::max(r - l, mx);
        int min_lat{INT_MAX}, min_fruit{};
        for (const auto &[f, idx] : seen)
        {
          if (idx < min_lat)
          {
            min_fruit = f;
            min_lat   = idx;
          }
        }

        l = min_lat + 1;
        seen.erase(min_fruit);
      }

      seen[fruits[r]] = r;
      r += 1;
    }

    return std::max(mx, n - l);
  }
};
