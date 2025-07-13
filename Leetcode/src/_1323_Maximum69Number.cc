#include <string>

class Solution
{
public:
  int maximum69Number(int n)
  {
    std::string s = std::to_string(n);
    for (char &c : s)
      if (c == '6')
      {
        c = '9';
        break;
      }

    return std::stoi(s);
  };
};
