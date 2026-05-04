#include <algorithm>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  std::vector<std::string> findItinerary(
      std::vector<std::vector<std::string>> &tickets)
  {
    std::unordered_map<std::string, std::multiset<std::string>> adj{};
    for (const auto &e : tickets)
      adj[e[0]].insert(e[1]);

    std::vector<std::string> ep{};
    std::stack<std::string> cp{};

    cp.push("JFK");
    while (!cp.empty())
    {
      auto u = cp.top();
      if (adj[u].empty())
      {
        ep.push_back(u);
        cp.pop();
      }
      else
      {
        auto v = *adj[u].begin();
        cp.push(v);
        adj[u].erase(adj[u].begin());
      }
    }

    std::reverse(ep.begin(), ep.end());
    return ep;
  }
};
