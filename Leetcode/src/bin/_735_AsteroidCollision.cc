#include <cstdlib>
#include <vector>

class Solution
{
public:
  std::vector<int> asteroidCollision(std::vector<int> &asteroids)
  {
    std::vector<int> belt{};
    for (int e : asteroids)
    {
      if (e > 0)
        belt.push_back(e);
      else
      {
        while (!belt.empty() && belt.back() > 0 && belt.back() <= std::abs(e))
        {
          if (belt.back() == std::abs(e))
          {
            belt.pop_back();
            goto nxt;
          }
          else
            belt.pop_back();
        }
        if (belt.empty() || belt.back() < 0)
          belt.push_back(e);
      nxt:
      }
    }

    return belt;
  }
};
