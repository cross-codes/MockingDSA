class Solution
{
public:
  double knightProbability(int n, int k, int row, int column)
  {
    int dx[8] = {1, 2, 1, 2, -1, -2, -1, -2};
    int dy[8] = {2, 1, -2, -1, 2, 1, -2, -1};
    double probability[n][n][k + 1];

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
        for (int m = 0; m <= k; m++)
          probability[y][x][m] = 0.00;

    probability[row][column][0] = 1.00;

    auto in_grid                = [&n](int y, int x) -> bool {
      return !(y < 0 || y >= n || x < 0 || x >= n);
    };

    for (int m = 1; m <= k; m++)
      for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
          for (int i = 0; i < 8; i++)
          {
            int X{x + dx[i]}, Y{y + dy[i]};
            if (in_grid(Y, X))
              probability[Y][X][m] += probability[y][x][m - 1] / 8.00;
          }

    double prob_on_board{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
        prob_on_board += probability[y][x][k];

    return prob_on_board;
  }
};
