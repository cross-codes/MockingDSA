#include <string>
#include <vector>

class Solution
{
public:
  int possibleStringCount(std::string word)
  {
    int n = static_cast<int>(word.size());
    std::vector<int> groups{};

    int win_start{}, win_char;
    bool in_window{};
    for (int i = 0; i < n; i++)
    {
      if (!in_window)
      {
        in_window = true;
        win_start = i;
        win_char  = word[i];
      }
      else
      {
        if (word[i] != win_char)
        {
          groups.push_back(i - win_start);
          win_start = i;
          win_char  = word[i];
        }
      }
    }

    groups.push_back(n - win_start);

    int res{};
    for (int f : groups)
      if (f > 0)
        res += f - 1;

    return res + 1;
  }
};
