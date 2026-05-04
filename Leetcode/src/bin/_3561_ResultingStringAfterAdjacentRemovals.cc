#include <stack>
#include <string>

class Solution
{
public:
  std::string resultingString(std::string s)
  {
    int n{static_cast<int>(s.length())};

    std::stack<char> excess{};
    for (int i = 0; i < n; i++)
    {
      if (excess.empty())
      {
        excess.push(s[i]);
        continue;
      }

      char prev = excess.top();
      if (std::abs(prev - s[i]) == 1 ||
          (std::min(prev, s[i]) == 'a' && std::max(prev, s[i]) == 'z'))
        excess.pop();
      else
        excess.push(s[i]);
    }

    std::string ans{};
    ans.resize(excess.size());
    auto it = ans.rbegin();

    while (!excess.empty())
    {
      *it = excess.top();
      excess.pop();
      ++it;
    }

    return ans;
  }
};
