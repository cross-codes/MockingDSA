#include <algorithm>
#include <set>
#include <vector>

class Solution
{
private:
  enum EventType
  {
    START,
    QUERY,
    END
  };

public:
  std::vector<int> minInterval(std::vector<std::vector<int>> &intervals,
                               std::vector<int> &queries)
  {
    std::vector<std::vector<int>> events{};
    int n = static_cast<int>(intervals.size());
    int q = static_cast<int>(queries.size());

    for (int i = 0; i < n; i++)
    {
      events.push_back({intervals[i][0], EventType::START, i});
      events.push_back({intervals[i][1], EventType::END, i});
    }

    for (int i = 0; i < q; i++)
      events.push_back({queries[i], EventType::QUERY, i});

    std::vector<int> res(q, 0);
    std::multiset<int> seen{};

    std::sort(events.begin(), events.end());
    for (const auto &e : events)
    {
      int point = e[0], type = e[1], idx = e[2];
      if (type == EventType::START)
      {
        int r = intervals[idx][1];
        seen.emplace(r - point + 1);
      }
      else if (type == EventType::END)
      {
        int l = intervals[idx][0];
        seen.erase(seen.find(point - l + 1));
      }
      else
      {
        if (!seen.empty())
          res[idx] = *seen.begin();
        else
          res[idx] = -1;
      }
    }

    return res;
  }
};
