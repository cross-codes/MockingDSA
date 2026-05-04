#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string> &wordList)
  {
    std::unordered_map<std::string, int> dist{};

    auto differs_by_one = [](std::string s1, std::string s2) -> bool {
      int n = static_cast<int>(s1.size());

      bool once{};
      for (int i = 0; i < n; i++)
        if (s1[i] != s2[i])
        {
          if (!once)
            once = true;
          else
            return false;
        }

      return once;
    };

    std::queue<std::string> queue{};
    queue.emplace(beginWord);
    while (!queue.empty())
    {
      auto str = queue.front();
      queue.pop();

      if (str == endWord)
        return dist[str] + 1;

      int d = dist[str];
      for (std::string word : wordList)
      {
        if (differs_by_one(str, word) && dist.find(word) == dist.end())
        {
          dist[word] = d + 1;
          queue.emplace(word);
        }
      }
    }

    return 0;
  }
};
