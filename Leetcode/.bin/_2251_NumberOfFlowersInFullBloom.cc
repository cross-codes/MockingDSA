#include <algorithm>
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
  std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> &flowers,
                                    std::vector<int> &people)
  {
    int n = static_cast<int>(flowers.size());
    std::vector<std::vector<int>> events{};

    for (int i = 0; i < n; i++)
    {
      int s = flowers[i][0], e = flowers[i][1];
      events.push_back({s, EventType::START, i});
      events.push_back({e, EventType::END, i});
    }

    int q = static_cast<int>(people.size());
    for (int i = 0; i < q; i++)
      events.push_back({people[i], EventType::QUERY, i});

    std::sort(events.begin(), events.end());

    int cnt{};
    std::vector<int> res(q, 0);
    for (const auto &v : events)
    {
      if (v[1] == EventType::START)
        cnt += 1;
      else if (v[1] == EventType::END)
        cnt -= 1;
      else
        res[v[2]] = cnt;
    }

    return res;
  }
};
