#include <algorithm>
#include <string>
#include <vector>

class Solution
{
public:
  int maxDiff(int num)
  {
    std::string str = std::to_string(num);
    int n{static_cast<int>(str.size())};
    std::vector<int> replacements{};

    auto replace = [&replacements, &n](std::string str, char x,
                                       char y) -> void {
      if (y == '0' && str[0] == x)
        return;

      for (int i = 0; i < n; i++)
        if (str[i] == x)
          str[i] = y;

      replacements.push_back(std::stoi(str));
    };

    replacements.push_back(std::stoi(str));
    for (char x = '0'; x <= '9'; x++)
      for (char y = '0'; y <= '9'; y++)
        replace(str, x, y);

    int max = *std::max_element(replacements.begin(), replacements.end());
    int min = *std::min_element(replacements.begin(), replacements.end());

    return max - min;
  }
};
