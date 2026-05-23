#include <algorithm>
#include <array>
#include <string>
#include <vector>

class Solution
{
public:
  std::string sortVowels(std::string s)
  {
    int n = static_cast<int>(s.size());
    std::array<std::pair<int, int>, 26> freq{};
    freq.fill({0, -1});

    std::array<char, 5> vowels = {'a', 'e', 'i', 'o', 'u'};
    std::vector<char> in_vowels{};
    for (int i = 0; i < n; i++)
    {
      char c = s[i];
      freq[c - 'a'].first += 1;
      if (freq[c - 'a'].second == -1)
      {
        freq[c - 'a'].second = i;
      }

      if (std::find(vowels.begin(), vowels.end(), c) != vowels.end())
      {
        in_vowels.push_back(c);
      }
    }

    auto cmp = [&](const char &c1, const char &c2) -> bool {
      if (freq[c1 - 'a'].first == freq[c2 - 'a'].first)
      {
        return freq[c1 - 'a'].second < freq[c2 - 'a'].second;
      }

      return freq[c1 - 'a'].first > freq[c2 - 'a'].first;
    };

    std::sort(in_vowels.begin(), in_vowels.end(), cmp);
    int vidx{};
    std::string res{};
    for (char c : s)
    {
      if (std::find(vowels.begin(), vowels.end(), c) != vowels.end())
      {
        res.push_back(in_vowels[vidx]);
        vidx += 1;
      }
      else
      {
        res.push_back(c);
      }
    }

    return res;
  }
};
