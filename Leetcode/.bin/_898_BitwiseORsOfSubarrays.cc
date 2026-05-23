#include <unordered_set>
#include <vector>

class Solution
{
public:
  int subarrayBitwiseORs(std::vector<int> &arr)
  {
    std::unordered_set<int> ans{}, cur{};
    cur.insert(0);
    for (int e : arr)
    {
      std::unordered_set<int> cur2{};
      for (int f : cur)
        cur2.insert(f | e);

      cur2.insert(e);
      cur.swap(cur2);
      ans.insert(cur.begin(), cur.end());
    }

    return static_cast<int>(ans.size());
  }
};
