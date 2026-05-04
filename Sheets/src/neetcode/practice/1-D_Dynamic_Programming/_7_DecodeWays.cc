#include <cstring>
#include <string>

class Solution
{
public:
  int numDecodings(std::string s)
  {
    int n = static_cast<int>(s.length());
    // num_ways[i] -> number of ways of interpreting i'th suffix
    int num_ways[n + 1];
    std::memset(num_ways, 0x00, sizeof(int) * n);
    num_ways[n] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
      if (s[i] == '0')
        num_ways[i] = 0;
      else
      {
        std::string comb{s[i]};
        if (std::stoi(comb) <= 26)
          num_ways[i] += num_ways[i + 1];

        if (i <= n - 2)
        {
          comb += s[i + 1];
          if (std::stoi(comb) <= 26)
            num_ways[i] += num_ways[i + 2];
        }
      }
    }

    return num_ways[0];
  }
};
