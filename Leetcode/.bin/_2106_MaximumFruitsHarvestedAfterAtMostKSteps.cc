#include <unordered_map>
#include <vector>

class Solution
{
public:
  int maxTotalFruits(std::vector<std::vector<int>> &fruits, int startPos, int k)
  {
    startPos += 1;

    int prefix[200002];
    prefix[0] = 0;

    std::unordered_map<int, int> fruit_map{};
    for (const auto &v : fruits)
      fruit_map[v[0] + 1] = v[1];

    for (int i = 1; i < 200002; i++)
    {
      prefix[i] = prefix[i - 1];
      if (fruit_map.contains(i))
        prefix[i] += fruit_map[i];
    }

    int mxf{};
    for (int x = 0; x <= std::min(startPos - 1, k); x++)
    {
      int l = startPos - x;
      int r = std::min(200001, l + (k - x));
      mxf   = std::max(mxf, prefix[r] - prefix[l - 1]);
    }

    for (int x = 0; x <= std::min(k, 200001 - startPos); x++)
    {
      int r = startPos + x;
      int l = std::max(1, r - (k - x));
      mxf   = std::max(mxf, prefix[r] - prefix[l - 1]);
    }

    return mxf;
  }
};
