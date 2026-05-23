#include <string>

class Solution
{
public:
  int maxRepeating(std::string sequence, std::string word)
  {

    int n{static_cast<int>(sequence.length())},
        m{static_cast<int>(word.length())};

    if (m > n)
      return 0;

    int max{};
    for (int k = 0; k <= n / m; k++)
    {
      std::string test{};
      for (int i = 0; i < k; i++)
        test += word;
      if (sequence.find(test) != sequence.npos)
        max = k;
      else
        break;
    }

    return max;
  }
};
