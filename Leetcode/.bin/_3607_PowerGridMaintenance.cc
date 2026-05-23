#include <cstring>
#include <set>
#include <unordered_map>
#include <vector>

class Solution
{
private:
  struct DisjointSetForest
  {
  public:
    std::vector<int> sizes, parents;

    DisjointSetForest(int n) : sizes(n), parents(n)
    {
      for (int u = 0; u < n; u++)
        make_set(u);
    }

    void make_set(int u)
    {
      parents[u] = u;
      sizes[u]   = 1;
    }

    int find_set(int u)
    {
      if (parents[u] == u)
        return u;
      else
      {
        parents[u] = find_set(parents[u]);
        return parents[u];
      }
    }

    bool unite(int x, int y)
    {
      int x_root{find_set(x)}, y_root{find_set(y)};

      if (x_root == y_root)
        return false;

      if (sizes[x_root] < sizes[y_root])
        std::swap(x_root, y_root);

      sizes[x_root] += sizes[y_root];
      parents[y_root] = x_root;

      return true;
    }
  };

public:
  std::vector<int> processQueries(int c,
                                  std::vector<std::vector<int>> &connections,
                                  std::vector<std::vector<int>> &queries)
  {
    DisjointSetForest dsu(c);

    std::vector<int> adj[c];
    for (const auto &vec : connections)
    {
      int from = vec[0] - 1, to = vec[1] - 1;
      adj[from].push_back(to);
      adj[to].push_back(from);
    }

    bool visited[c];
    std::memset(visited, false, sizeof(bool) * c);

    auto dfs = [&visited, &adj, &dsu](auto &&dfs, int u,
                                      std::set<int> &vertices) -> void {
      vertices.insert(u);
      visited[u] = true;

      for (const auto &v : adj[u])
        if (!visited[v])
        {
          dsu.unite(u, v);
          dfs(dfs, v, vertices);
        }
    };

    std::unordered_map<int, std::set<int>> cc_sets{};
    for (int i = 0; i < c; i++)
    {
      if (!visited[i])
      {
        std::set<int> cc_vertices{};
        dfs(dfs, i, cc_vertices);

        int repr      = dsu.find_set(i);
        cc_sets[repr] = cc_vertices;
      }
    }

    std::vector<int> res{};
    for (const auto &vec : queries)
    {
      int type = vec[0], x = vec[1] - 1;
      if (type == 1)
      {
        auto &set = cc_sets[dsu.find_set(x)];
        if (set.empty())
          res.push_back(-1);
        else
        {
          if (set.contains(x))
            res.push_back(x + 1);
          else
            res.push_back(*set.begin() + 1);
        }
      }
      else
      {
        auto &set = cc_sets[dsu.find_set(x)];
        set.erase(x);
      }
    }

    return res;
  }
};

int main()
{
  int c                                 = 5;
  std::vector<std::vector<int>> con     = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::vector<std::vector<int>> queries = {
      {1, 3}, {2, 1}, {1, 1}, {2, 2}, {1, 2}};
  Solution().processQueries(c, con, queries);
}
