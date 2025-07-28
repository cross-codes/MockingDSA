#include <deque>
#include <string>

class Solution
{
public:
  int maxConsecutiveAnswers(std::string s, int k)
  {
    int n = static_cast<int>(s.size());
    // T
    int l{}, r{}, mx{}, cnt{};
    std::deque<int> pos{};
    while (r < n)
    {
      if (cnt < k)
      {
        if (s[r] == 'F')
        {
          pos.push_back(r);
          cnt += 1;
          mx = std::max(mx, r - l + 1);
        }
      }
      else
      {
        if (s[r] == 'T')
          mx = std::max(mx, r - l + 1);
        else
        {
          mx = std::max(mx, r - l);
          l  = pos.front() + 1;
          pos.pop_front();
          pos.push_back(r);
        }
      }
      r += 1;
    }

    mx = std::max(mx, n - l);

    // F
    l = 0, r = 0, cnt = 0;
    int nmx{};
    pos.clear();
    while (r < n)
    {
      if (cnt < k)
      {
        if (s[r] == 'T')
        {
          pos.push_back(r);
          cnt += 1;
          nmx = std::max(nmx, r - l + 1);
        }
      }
      else
      {
        if (s[r] == 'F')
          nmx = std::max(nmx, r - l + 1);
        else
        {
          nmx = std::max(nmx, r - l);
          l   = pos.front() + 1;
          pos.pop_front();
          pos.push_back(r);
        }
      }
      r += 1;
    }

    nmx = std::max(nmx, n - l);

    return std::max(mx, nmx);
  }
};
