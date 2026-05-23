#include <array>
#include <climits>
#include <iostream>
#include <string>

class Solution
{
private:
  auto contains_str_(const std::array<int, 52> &original,
                     const std::array<int, 52> &test) const
  {
    for (int i = 0; i < 52; i++)
      if (original[i] != 0)
        if (original[i] > test[i])
          return false;

    return true;
  }

  auto mapper_(char c) -> int
  {
    if (isupper(c))
    {
      return c - 'A';
    }
    else
    {
      return 26 + c - 'a';
    }
  }

public:
  std::string minWindow(std::string s, std::string t)
  {
    int n{static_cast<int>(s.length())};
    int m{static_cast<int>(t.length())};

    std::array<int, 52> original_freq{};
    for (int i = 0; i < m; i++)
      original_freq[mapper_(t[i])] += 1;

    int l{}, r{};
    int min_length{INT_MAX};
    int min_l{}, min_r{n - 1};
    std::array<int, 52> window_freq{};
    window_freq[mapper_(s[0])] += 1;

    while (r < n)
    {
      if (!contains_str_(original_freq, window_freq))
      {
        r += 1;
        if (r < n)
          window_freq[mapper_(s[r])] += 1;
      }
      else
      {
        if (r - l + 1 < min_length)
        {
          min_l      = l;
          min_r      = r;
          min_length = r - l + 1;
        }
        if (l >= r)
          return s.substr(min_l, min_length);

        l += 1;
        window_freq[mapper_(s[l - 1])] -= 1;
      }
    }

    if (l < n)
    {
      do
      {
        if (contains_str_(original_freq, window_freq) && r - l + 1 < min_length)
        {
          min_l      = l;
          min_r      = r;
          min_length = r - l + 1;
        }

        window_freq[mapper_(s[l])] -= 1;
        l += 1;
      } while (l < n && contains_str_(original_freq, window_freq));
    }

    std::array<int, 52> final{};
    for (int i = min_l; i <= min_r; i++)
      final[mapper_(s[i])] += 1;

    if (contains_str_(original_freq, final))
      return s.substr(min_l, min_length);
    else
      return "";
  }
};
