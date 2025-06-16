#include <string>

class Solution
{
public:
  std::string countAndSay(int n)
  {
    std::string rle{"1"};

    auto get_rle = [](std::string_view s) -> std::string {
      std::string res{};
      size_t start = 0;
      char c       = s[start];
      size_t end   = s.find_first_not_of(c);

      if (end != std::string_view::npos)
      {
        res += std::to_string(end - start);
        res += c;
      }
      else
      {
        res += std::to_string(s.size() - start);
        res += c;
      }

      while (end != std::string_view::npos)
      {
        start = end;
        c     = s[start];
        end   = s.find_first_not_of(c, start);
        if (end != std::string_view::npos)
        {
          res += std::to_string(end - start);
          res += c;
        }
        else
        {
          res += std::to_string(s.size() - start);
          res += c;
        }
      }

      return res;
    };

    for (int i = 2; i <= n; i++)
      rle = get_rle(rle);

    return rle;
  }
};
