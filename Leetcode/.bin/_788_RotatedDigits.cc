#include <optional>
#include <string>

class Solution
{
public:
  int rotatedDigits(int n)
  {
    auto rotate = [](std::string s) -> std::optional<int> {
      std::string res{};
      int n = static_cast<int>(s.size());

      for (int i = 0; i < n; i++)
      {
        switch (s[i])
        {
        case '0':
          res.push_back('0');
          break;

        case '1':
          res.push_back('1');
          break;

        case '2':
          res.push_back('5');
          break;

        case '5':
          res.push_back('2');
          break;

        case '6':
          res.push_back('9');
          break;

        case '8':
          res.push_back('8');
          break;

        case '9':
          res.push_back('6');
          break;

        default:
          return std::nullopt;
        }
      }

      return std::stoi(res);
    };

    int cnt{};
    for (int i = 1; i <= n; i++)
    {
      auto res = rotate(std::to_string(i));
      if (res.has_value() && *res != i)
        cnt += 1;
    }

    return cnt;
  }
};
