#include <array>
#include <cstring>
#include <string>
#include <vector>

class Solution
{
private:
  auto can_cut_(std::array<int, 26> &farthest, std::array<bool, 26> &contains,
                int curpos) -> bool
  {
    for (int i = 0; i < 26; i++)
      if (contains[i] && farthest[i] > curpos)
        return false;

    return true;
  }

public:
  std::vector<int> partitionLabels(std::string s)
  {
    int n{static_cast<int>(s.length())};
    std::array<int, 26> farthest{};

    for (int i = n - 1; i >= 0; i--)
    {
      if (farthest[s[i] - 'a'] == 0)
        farthest[s[i] - 'a'] = i;
    }

    std::vector<int> res{};
    std::array<bool, 26> contains{};

    int l{};
    for (int r = 0; r < n; r++)
    {
      contains[s[r] - 'a'] = true;
      if (can_cut_(farthest, contains, r))
      {
        res.push_back(r - l + 1);
        l = r + 1;
        std::memset(contains.data(), false, sizeof(bool) * 26);
      }
    }

    return res;
  }
};
