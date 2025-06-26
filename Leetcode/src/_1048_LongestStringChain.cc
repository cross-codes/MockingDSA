#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>

class Solution
{
public:
  int longestStrChain(std::vector<std::string> &words)
  {
    int n             = static_cast<int>(words.size());

    auto STRING_ORDER = [](const std::string &a, const std::string &b) -> bool {
      return a.size() < b.size();
    };

    std::sort(words.begin(), words.end(), STRING_ORDER);

    auto can_construct = [](const std::string &a,
                            const std::string &b) -> bool {
      int n = static_cast<int>(a.size());

      bool once{};
      for (int i = 0, j = 0; i < n && j < n - 1; i++, j++)
      {
        if (a[i] != b[j] && once)
          return false;
        else if (a[i] != b[j])
        {
          once = true;
          if (a[i + 1] == b[j])
            i += 1;
          else
            return false;
        }
      }

      return true;
    };

    int l[n];
    std::memset(l, 0x00, sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
      int mx{};
      size_t tsz = words[i].size() - 1;
      for (int j = i - 1; j >= 0; j--)
      {
        if (words[j].size() < tsz)
          break;

        if (words[j].size() == tsz + 1)
          continue;

        if (can_construct(words[i], words[j]))
          mx = std::max(mx, l[j] + 1);
      }

      l[i] = std::max(mx, 1);
    }

    return *std::max_element(l, l + n);
  }
};
