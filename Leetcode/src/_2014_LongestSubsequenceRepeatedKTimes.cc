#include <array>
#include <queue>
#include <string>
#include <vector>

class Solution
{
public:
  std::string longestSubsequenceRepeatedK(std::string s, int k)
  {
    int n = static_cast<int>(s.length());

    // l x k = n -> l = n / k so lmax = 8;
    // complete search + test at each iteration: O(n x 2^8).

    auto reps = [&s, &n](const std::string &a) -> int {
      int rep{}, word_ptr{};
      int m = static_cast<int>(a.length());

      for (int i = 0; i < n; i++)
      {
        if (s[i] == a[word_ptr])
        {
          if (word_ptr == m - 1)
          {
            rep += 1;
            word_ptr = 0;
          }
          else
            word_ptr += 1;
        }
      }

      return rep;
    };

    std::array<int, 26> freq{};
    for (char c : s)
      freq[c - 'a'] += 1;

    std::vector<char> candidates{};
    for (int i = 0; i < 26; i++)
      if (freq[i] >= k)
        candidates.push_back(static_cast<char>(i + 'a'));

    std::queue<std::string> queue{};
    queue.emplace("");
    std::string res{};

    while (!queue.empty())
    {
      auto str = queue.front();
      queue.pop();
      for (char c : candidates)
      {
        str += c;
        if (reps(str) >= k)
        {
          res = str;
          queue.emplace(str);
        }
        str.pop_back();
      }
    }

    return res;
  }
};
