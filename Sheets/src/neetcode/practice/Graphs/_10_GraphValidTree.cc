#include <numeric>
#include <vector>

class Solution
{
private:
  bool is_tree{};
  std::vector<int> vertices_{};
  std::vector<std::vector<int>> adj_{};
  std::vector<bool> visited_{};

  void dfs_()
  {
    bool is_first_pass{true};
    for (const auto &vertex : vertices_)
    {
      if (!visited_[vertex])
      {
        if (!is_first_pass)
          is_tree = false;
        else
          is_first_pass = false;

        dfs_visit_(vertex);
      }
    }
  }

  void dfs_visit_(int vertex)
  {
    visited_[vertex] = true;
    for (const auto &v : adj_[vertex])
    {
      if (!visited_[v])
        dfs_visit_(v);
    }
  }

public:
  Solution()
  {
    is_tree = true;
  }

  bool validTree(int n, std::vector<std::vector<int>> &edges)
  {
    if (static_cast<int>(edges.size()) >= n)
      return false;

    vertices_.resize(n);
    adj_.resize(n);
    visited_.resize(n, false);
    std::iota(vertices_.begin(), vertices_.end(), 0);

    for (const auto &edge : edges)
    {
      int v1{edge[0]}, v2{edge[1]};
      adj_[v1].push_back(v2);
      adj_[v2].push_back(v1);
    }

    dfs_();
    return is_tree;
  }
};
