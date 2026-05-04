#include <vector>

class SubrectangleQueries
{
private:
  std::vector<std::vector<int>> grid_{};
  int n, m;

public:
  SubrectangleQueries(std::vector<std::vector<int>> &rectangle)
      : grid_(rectangle)
  {
    n = static_cast<int>(grid_.size());
    m = static_cast<int>(grid_[0].size());
  }

  void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
  {
    int y1{row1}, y2{row2};
    int x1{col1}, x2{col2};

    for (int y = y1; y <= y2; y++)
      for (int x = x1; x <= x2; x++)
        grid_[y][x] = newValue;
  }

  int getValue(int row, int col)
  {
    return grid_[row][col];
  }
};
