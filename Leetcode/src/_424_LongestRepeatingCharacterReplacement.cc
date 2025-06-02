#include <algorithm>
#include <array>
#include <string>

class Solution
{
public:
  int characterReplacement(const std::string &s, int k)
  {
    std::array<int, 26> freq{};

    int n{static_cast<int>(s.length())};
    int max_freq{}, l{}, r{}, max_window{};
    while (r < n)
    {
      freq[s[r] - 'A']++;
      max_freq = std::max(max_freq, freq[s[r] - 'A']);

      while (r - l + 1 - max_freq > k)
      {
        freq[s[l] - 'A']--;
        l++;
      }

      max_window = std::max(max_window, r - l + 1);
      r += 1;
    }
    return max_window;
  }
};
