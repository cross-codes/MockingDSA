#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  int wordCount(std::vector<std::string> &startWords,
                std::vector<std::string> &targetWords)
  {
    std::unordered_set<std::string> strs[27];
    for (const std::string &w : startWords)
    {
      bool a[26]{};
      for (char c : w)
        a[c - 'a'] = true;

      for (int i = 0; i < 26; i++)
      {
        if (!a[i])
        {
          std::string nw = w + static_cast<char>(i + 'a');
          std::sort(nw.begin(), nw.end());
          strs[nw.length()].insert(nw);
        }
      }
    }

    int cnt{};
    for (std::string &w : targetWords)
    {
      std::sort(w.begin(), w.end());
      if (strs[w.length()].contains(w))
        cnt += 1;
    }

    return cnt;
  }
};
