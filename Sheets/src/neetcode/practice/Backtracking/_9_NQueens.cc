#include <string>
#include <vector>

class Solution {
public:
  std::vector<std::vector<std::string>> res{};
  std::vector<int> column{}, diag1{}, diag2{};

  void search(int y, std::vector<std::string> comb, int n) {
    if (y == n) {
      res.push_back(comb);
      return;
    }

    for (int x = 0; x < n; x++) {
      if (column[x] || diag1[x + y] || diag2[x - y + n - 1])
        continue;

      std::string row(n, '.');
      row[x] = 'Q';

      comb.push_back(row);
      column[x] = diag1[x + y] = diag2[x - y + n - 1] = 1;
      search(y + 1, comb, n);
      comb.pop_back();
      column[x] = diag1[x + y] = diag2[x - y + n - 1] = 0;
    }
  }

  std::vector<std::vector<std::string>> solveNQueens(int n) {
    column.resize(n, 0);
    diag1.resize(2 * n - 1, 0);
    diag2.resize(2 * n - 1, 0);
    search(0, {}, n);
    return res;
  }
};
