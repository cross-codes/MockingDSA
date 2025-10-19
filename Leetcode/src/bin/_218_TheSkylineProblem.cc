#include <algorithm>
#include <set>
#include <vector>

class Solution
{
  enum BorderType
  {
    START,
    END
  };

public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>> &buildings)
  {
    std::vector<std::vector<int>> borders{};
    int n = static_cast<int>(buildings.size());

    for (int i = 0; i < n; i++)
    {
      int l = buildings[i][0], r = buildings[i][1], h = buildings[i][2];
      borders.push_back({l, BorderType::START, h});
      borders.push_back({r, BorderType::END, h});
    }

    auto BORDER_ORDER = [](const std::vector<int> &a,
                           const std::vector<int> &b) -> bool {
      int cmp = a[0] - b[0];
      if (cmp == 0)
      {
        int cmp2 = a[1] - b[1];
        if (cmp2 == 0)
          return a[1] == BorderType::END ? a[2] < b[2] : a[2] > b[2];
        else
          return cmp2 < 0;
      }
      else
        return cmp < 0;
    };

    std::vector<std::vector<int>> skyline{};
    std::sort(borders.begin(), borders.end(), BORDER_ORDER);

    std::multiset<int> heights{};
    for (const auto &b : borders)
    {
      int point = b[0], type = b[1], height = b[2];
      if (type == BorderType::START)
      {
        // potential new height, or nothing new to see
        if (heights.empty())
        {
          heights.insert(height);
          skyline.push_back({point, height});
        }
        else
        {
          if (*heights.rbegin() < height)
            skyline.push_back({point, height});
          heights.insert(height);
        }
      }
      else
      {
        // potential new height
        if (*heights.rbegin() == height)
        {
          heights.erase(heights.find(height));
          if (heights.empty() || *heights.rbegin() < height)
            skyline.push_back({point, heights.empty() ? 0 : *heights.rbegin()});
        }
        else
          heights.erase(heights.find(height));
      }
    }

    return skyline;
  }
};
