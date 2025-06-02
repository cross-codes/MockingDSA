#include <vector>

class Solution
{
private:
  enum class Sink
  {
    PACIFIC,
    ATLANTIC,
    BOTH,
    NONE
  };

  std::vector<std::vector<Sink>> sinks_{};

  auto adjacent_cell_sink_(Sink type, int y, int x, int n, int m,
                           const std::vector<std::vector<int>> &heights) -> bool
  {
    bool res = false;
    if (x > 0 && heights[y][x - 1] <= heights[y][x])
      res = res || (sinks_[y][x - 1] == type || sinks_[y][x - 1] == Sink::BOTH);
    if (y > 0 && heights[y - 1][x] <= heights[y][x])
      res = res || (sinks_[y - 1][x] == type || sinks_[y - 1][x] == Sink::BOTH);
    if (x < m - 1 && heights[y][x + 1] <= heights[y][x])
      res = res || (sinks_[y][x + 1] == type || sinks_[y][x + 1] == Sink::BOTH);
    if (y < n - 1 && heights[y + 1][x] <= heights[y][x])
      res = res || (sinks_[y + 1][x] == type || sinks_[y + 1][x] == Sink::BOTH);

    return res;
  }

public:
  std::vector<std::vector<int>> pacificAtlantic(
      std::vector<std::vector<int>> &heights)
  {
    int n{static_cast<int>(heights.size())};
    int m{static_cast<int>(heights[0].size())};

    sinks_ =
        std::vector<std::vector<Sink>>(n, std::vector<Sink>(m, Sink::NONE));

    for (int x = 0; x < m - 1; x++)
      sinks_[0][x] = Sink::PACIFIC;

    for (int y = 0; y < n - 1; y++)
      sinks_[y][0] = Sink::PACIFIC;

    for (int x = 1; x < m; x++)
      sinks_[n - 1][x] = Sink::ATLANTIC;

    for (int y = 1; y < n; y++)
      sinks_[y][m - 1] = Sink::ATLANTIC;

    sinks_[0][m - 1] = Sink::BOTH;
    sinks_[n - 1][0] = Sink::BOTH;

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (sinks_[y][x] == Sink::NONE || sinks_[y][x] == Sink::ATLANTIC)
        {
          if (adjacent_cell_sink_(Sink::PACIFIC, y, x, n, m, heights))
          {
            if (sinks_[y][x] == Sink::ATLANTIC)
              sinks_[y][x] = Sink::BOTH;
            else
              sinks_[y][x] = Sink::PACIFIC;
          }
        }
      }

    for (int y = n - 1; y >= 0; y--)
      for (int x = 0; x < m; x++)
      {
        if (sinks_[y][x] == Sink::NONE || sinks_[y][x] == Sink::ATLANTIC)
        {
          if (adjacent_cell_sink_(Sink::ATLANTIC, y, x, n, m, heights))
          {
            if (sinks_[y][x] == Sink::PACIFIC)
              sinks_[y][x] = Sink::BOTH;
            else
              sinks_[y][x] = Sink::ATLANTIC;
          }
        }
      }

    std::vector<std::vector<int>> res{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        if (sinks_[y][x] == Sink::BOTH)
          res.push_back({y, x});

    return res;
  }
};
