#include <array>
#include <numeric>
#include <vector>

class Solution
{
  enum class Color
  {
    WHITE,
    GRAY,
    BLACK
  };

  bool cycle_{false};
  std::array<Color, 1000> colors_{};
  std::vector<int> vertices_{};
  std::vector<std::vector<int>> adj_{};

  void dfs_()
  {
    colors_.fill(Color::WHITE);

    for (const int &vertex : vertices_)
    {
      if (colors_[vertex] == Color::WHITE)
      {
        dfs_visit_(vertex);
      }
    }
  }

  void dfs_visit_(int vertex)
  {
    colors_[vertex] = Color::GRAY;

    for (const int &v : adj_[vertex])
    {
      if (colors_[v] == Color::WHITE)
      {
        dfs_visit_(v);
      }
      else if (colors_[v] == Color::GRAY)
      {
        cycle_ = true;
      }
    }
    colors_[vertex] = Color::BLACK;
  }

public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites)
  {
    adj_.resize(numCourses, std::vector<int>());
    vertices_.resize(numCourses);
    for (const auto &edge : prerequisites)
    {
      int from{edge[0]}, to{edge[1]};
      adj_[from].push_back(to);
    }

    std::iota(vertices_.begin(), vertices_.end(), 0);
    dfs_();

    return !cycle_;
  }
};
