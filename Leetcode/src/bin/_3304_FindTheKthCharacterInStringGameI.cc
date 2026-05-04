#include <string>

class Solution
{
public:
  char kthCharacter(int k)
  {
    std::string manip{'a'};

    auto gen_nxt = [](const std::string a) -> std::string {
      std::string res{};

      for (char c : a)
      {
        if (c == 'z')
          res += 'a';
        else
          res += static_cast<char>(c + 1);
      }

      return res;
    };

    while (static_cast<int>(manip.length()) <= k)
    {
      auto nxt = gen_nxt(manip);
      manip += nxt;
    }

    return manip[k - 1];
  }
};
