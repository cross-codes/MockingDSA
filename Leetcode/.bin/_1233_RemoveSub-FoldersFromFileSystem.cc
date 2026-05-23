#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::string> removeSubfolders(std::vector<std::string> &folder)
  {
    int n = static_cast<int>(folder.size());
    std::sort(folder.begin(), folder.end());

    bool to_remove[n];
    std::memset(to_remove, false, sizeof to_remove);

    int L{}, R{1};
    std::string curr = folder[L];
    int curr_len     = static_cast<int>(folder[L].size());
    while (R < n)
    {
      int r_len = static_cast<int>(folder[R].size());
      if (folder[R].substr(0, curr_len) == curr && r_len > curr_len &&
          folder[R][curr_len] == '/')
      {
        to_remove[R] = 1;
        R += 1;
      }
      else
      {
        L        = R;
        curr     = folder[R];
        curr_len = static_cast<int>(folder[L].size());
        R += 1;
      }
    }

    std::vector<std::string> res{};
    for (int i = 0; i < n; i++)
      if (!to_remove[i])
        res.push_back(folder[i]);

    return res;
  }
};
