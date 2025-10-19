#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <string>

class Solution
{
public:
  int64_t kMirror(int k, int n)
  {
    auto conv_inv = [&k](int64_t n) -> std::string {
      std::string res{};
      std::string char_set = "0123456789";

      while (n != 0)
      {
        res.push_back(char_set[n % k]);
        n /= k;
      }

      return res;
    };

    auto is_palindrome = [](std::string s) -> bool {
      int n = static_cast<int>(s.length());
      int l{}, r{n - 1};
      while (l <= r)
      {
        if (s[l] != s[r])
          return false;
        l += 1;
        r -= 1;
      }

      return true;
    };

    int64_t sum{};
    int matches{};

    for (int i = 1; i <= 9; i++)
    {
      if (matches == n)
        return sum;

      if (is_palindrome(conv_inv(i)))
      {
        matches += 1;
        sum += i;
      }
    }

    for (int l = 2; true; l++)
    {
      if (l & 1)
      {
        int hl        = std::midpoint(1, l);
        int64_t start = static_cast<int64_t>(std::pow(10, hl - 1));
        int64_t end   = static_cast<int64_t>(std::pow(10, hl)) - 1;

        for (int64_t i = start; i <= end; i++)
        {
          if (matches == n)
            return sum;

          std::string lh = std::to_string(i), rh = lh;
          std::reverse(rh.begin(), rh.end());
          rh            = rh.substr(1, std::string::npos);
          int64_t equiv = std::stoll(lh + rh);
          if (is_palindrome(conv_inv(equiv)))
          {
            matches += 1;
            sum += equiv;
          }
        }
      }
      else
      {
        int hl        = std::midpoint(1, l);
        int64_t start = static_cast<int64_t>(std::pow(10, hl - 1));
        int64_t end   = static_cast<int64_t>(std::pow(10, hl)) - 1;

        for (int64_t i = start; i <= end; i++)
        {
          if (matches == n)
            return sum;

          std::string lh = std::to_string(i), rh = lh;
          std::reverse(rh.begin(), rh.end());
          int64_t equiv = std::stoll(lh + rh);
          if (is_palindrome(conv_inv(equiv)))
          {
            matches += 1;
            sum += equiv;
          }
        }
      }
    }
  }
};
