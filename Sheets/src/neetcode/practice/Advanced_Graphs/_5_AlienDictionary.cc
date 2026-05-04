#include <algorithm>
#include <string>
#include <vector>

class Solution
{
public:
  std::string foreignDictionary(std::vector<std::string> &words)
  {
    int n = static_cast<int>(words.size());

    std::vector<int> adj[26];

    for (int i = 0; i < n - 1; i++)
    {
      std::string w1 = words[i], w2 = words[i + 1];
      int len = static_cast<int>(std::min(w1.size(), w2.size()));
      int j{};
      while (j < len)
      {
        if (w1[j] != w2[j])
        {
          adj[w1[j] - 'a'].push_back(w2[j] - 'a');
          break;
        }
        j++;
      }

      if (j == len && w1.size() > w2.size())
        return "";
    }

    int colors[26]{}; // 0(W), 1(G), 2(B)
    std::string order{};

    auto dfs = [&order, &colors, &adj](auto &&dfs, int u, bool &cycle) -> void {
      colors[u] = 1;
      for (const int &v : adj[u])
      {
        if (colors[v] == 0)
          dfs(dfs, v, cycle);
        else if (colors[v] == 1)
          cycle = true;
      }

      order.push_back(static_cast<char>(u + 'a'));
      colors[u] = 2;
    };

    bool cycle{};
    for (int i = 0; i < 26; i++)
      if (colors[i] == 0)
        dfs(dfs, i, cycle);

    if (cycle)
      return "";

    std::reverse(order.begin(), order.end());
    return order;
  }
};
