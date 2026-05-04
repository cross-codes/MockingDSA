#include <string>
#include <vector>

class Solution
{
public:
  bool exist(std::vector<std::vector<char>> &board, std::string word)
  {
    int n{static_cast<int>(board.size())}, m{static_cast<int>(board[0].size())};

    bool res{};
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    auto visitable = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    auto dfs = [&board, &visited, &word, &res, &visitable, &dx,
                &dy](auto &&dfs, const int &y, const int &x, std::string &curr,
                     int index) -> void {
      if (curr.size() == word.size())
      {
        res |= true;
        return;
      }

      visited[y][x] = true;

      for (int i = 0; i < 4; i++)
      {
        int X{x + dx[i]}, Y{y + dy[i]};
        if (visitable(Y, X) && !visited[Y][X] && board[Y][X] == word[index])
        {
          curr.push_back(word[index]);
          dfs(dfs, Y, X, curr, index + 1);
          curr.pop_back();
        }
      }

      visited[y][x] = false;
    };

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        if (board[y][x] == word[0])
        {
          std::string curr{word[0]};
          dfs(dfs, y, x, curr, 1);
          if (res)
            return true;
        }

    return res;
  }
};
