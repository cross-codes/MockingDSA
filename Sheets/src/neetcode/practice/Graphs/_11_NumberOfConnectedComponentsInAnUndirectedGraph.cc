#include <numeric>
#include <vector>

class Solution
{
private:
  std::vector<int> vertices_;
  std::vector<std::vector<int>> adj_;
  std::vector<bool> visited_;

  int connected_components_{};

  void dfs_()
  {
    for (const auto &vertex : vertices_)
    {
      if (!visited_[vertex])
      {
        dfs_visit_(vertex);
        connected_components_ += 1;
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
    connected_components_ = 0;
  }

  int countComponents(int n, std::vector<std::vector<int>> &edges)
  {
    adj_.resize(n);
    vertices_.resize(n);
    visited_.resize(n, false);

    std::iota(vertices_.begin(), vertices_.end(), 0);
    for (const auto &edge : edges)
    {
      int v1{edge[0]}, v2{edge[1]};
      adj_[v1].push_back(vertices_[v2]);
      adj_[v2].push_back(vertices_[v1]);
    }

    dfs_();
    return connected_components_;
  }
};
