#include <string>
#include <vector>

class Solution {
public:
  int cnt = 0;

  void search(std::vector<std::vector<char>> &board, std::string cur,
              const std::string &word, unsigned int i, unsigned int j,
              std::size_t nrows, std::size_t ncols,
              std::vector<std::vector<bool>> visited) {
    if (i < 0 || i >= nrows || j < 0 || j >= ncols || visited[i][j] ||
        cur.size() > word.size()) {
      return;
    }

    cur += board[i][j];
    visited[i][j] = true;
    if (cur == word) {
      cnt++;
      return;
    }

    search(board, cur, word, i + 1, j, nrows, ncols, visited);
    if (cnt > 0)
      return;
    search(board, cur, word, i, j + 1, nrows, ncols, visited);
    if (cnt > 0)
      return;
    search(board, cur, word, i - 1, j, nrows, ncols, visited);
    if (cnt > 0)
      return;
    search(board, cur, word, i, j - 1, nrows, ncols, visited);
  }

  bool exist(std::vector<std::vector<char>> &board, std::string word) {
    char start = word[0];
    std::size_t nrows = board.size(), ncols = board[0].size();

    for (unsigned int i = 0; i < nrows; i++) {
      for (unsigned int j = 0; j < ncols; j++) {
        if (board[i][j] == start) {
          search(board, "", word, i, j, nrows, ncols,
                 std::vector<std::vector<bool>>(
                     nrows, std::vector<bool>(ncols, false)));
        }
        if (cnt > 0)
          return true;
      }
    }

    return cnt > 0;
  }
};
