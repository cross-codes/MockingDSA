#include <algorithm>
#include <string>

class Solution
{
public:
  int maxDistance(std::string s, int k)
  {
    int n          = static_cast<int>(s.length());

    auto greedy_NW = [&n](std::string s, int k) -> int {
      for (int i = 0; k != 0 && i < n; i++)
      {
        if (s[i] == 'S')
        {
          s[i] = 'N';
          k -= 1;
        }
        if (s[i] == 'E')
        {
          s[i] = 'W';
          k -= 1;
        }
      }

      int max_dis{};
      int x{}, y{};
      for (int i = 0; i < n; i++)
      {
        if (s[i] == 'N')
          y += 1;
        else if (s[i] == 'E')
          x += 1;
        else if (s[i] == 'W')
          x -= 1;
        else
          y -= 1;

        max_dis = std::max(max_dis, std::abs(x) + std::abs(y));
      }

      return max_dis;
    };

    auto greedy_NE = [&n](std::string s, int k) -> int {
      for (int i = 0; k != 0 && i < n; i++)
      {
        if (s[i] == 'S')
        {
          s[i] = 'N';
          k -= 1;
        }
        if (s[i] == 'W')
        {
          s[i] = 'E';
          k -= 1;
        }
      }

      int max_dis{};
      int x{}, y{};
      for (int i = 0; i < n; i++)
      {
        if (s[i] == 'N')
          y += 1;
        else if (s[i] == 'E')
          x += 1;
        else if (s[i] == 'W')
          x -= 1;
        else
          y -= 1;

        max_dis = std::max(max_dis, std::abs(x) + std::abs(y));
      }

      return max_dis;
    };

    auto greedy_SW = [&n](std::string s, int k) -> int {
      for (int i = 0; k != 0 && i < n; i++)
      {
        if (s[i] == 'N')
        {
          s[i] = 'S';
          k -= 1;
        }
        if (s[i] == 'E')
        {
          s[i] = 'W';
          k -= 1;
        }
      }

      int max_dis{};
      int x{}, y{};
      for (int i = 0; i < n; i++)
      {
        if (s[i] == 'N')
          y += 1;
        else if (s[i] == 'E')
          x += 1;
        else if (s[i] == 'W')
          x -= 1;
        else
          y -= 1;

        max_dis = std::max(max_dis, std::abs(x) + std::abs(y));
      }

      return max_dis;
    };

    auto greedy_SE = [&n](std::string s, int k) -> int {
      for (int i = 0; k != 0 && i < n; i++)
      {
        if (s[i] == 'N')
        {
          s[i] = 'S';
          k -= 1;
        }
        if (s[i] == 'W')
        {
          s[i] = 'E';
          k -= 1;
        }
      }

      int max_dis{};
      int x{}, y{};
      for (int i = 0; i < n; i++)
      {
        if (s[i] == 'N')
          y += 1;
        else if (s[i] == 'E')
          x += 1;
        else if (s[i] == 'W')
          x -= 1;
        else
          y -= 1;

        max_dis = std::max(max_dis, std::abs(x) + std::abs(y));
      }

      return max_dis;
    };

    return std::max(
        greedy_NW(s, k),
        std::max(greedy_NE(s, k), std::max(greedy_SW(s, k), greedy_SE(s, k))));
  }
};
