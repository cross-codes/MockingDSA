#include <array>
#include <cctype>
#include <vector>

class Solution {
private:
  bool rowValidator_(const std::vector<std::vector<char>> &board, int rowNum) {
    std::array<int, 9> freq = {};
    for (int i = 0; i < 9; i++) {
      char c = board[rowNum][i];
      if (c == '.')
        continue;
      else if (std::isdigit(c)) {
        if (freq[c - '1'] == 1)
          return false;
        else
          freq[c - '1']++;
      }
    }

    return true;
  }

  bool columnValidator_(const std::vector<std::vector<char>> &board,
                        int colNum) {
    std::array<int, 9> freq = {};
    for (int i = 0; i < 9; i++) {
      char c = board[i][colNum];
      if (c == '.')
        continue;
      else if (std::isdigit(c)) {
        if (freq[c - '1'] == 1)
          return false;
        else
          freq[c - '1']++;
      }
    }

    return true;
  }

  bool gridValidator_(const std::vector<std::vector<char>> &board,
                      int upperLeftColNum, int upperLeftRowNum) {
    std::array<int, 9> freq = {};
    for (int rowIterator = upperLeftRowNum; rowIterator < upperLeftRowNum + 3;
         rowIterator++) {
      for (int colIterator = upperLeftColNum; colIterator < upperLeftColNum + 3;
           colIterator++) {
        char c = board[rowIterator][colIterator];
        if (c == '.')
          continue;
        else if (std::isdigit(c)) {
          if (freq[c - '1'] == 1)
            return false;
          else
            freq[c - '1']++;
        }
      }
    }

    return true;
  }

public:
  bool isValidSudoku(std::vector<std::vector<char>> &board) {
    bool res;
    for (int i = 0; i < 9; i++) {
      res = rowValidator_(board, i);
      if (!res)
        return false;
    }

    for (int i = 0; i < 9; i++) {
      res = columnValidator_(board, i);
      if (!res)
        return false;
    }

    for (int i = 0; i < 9; i += 3) {
      for (int j = 0; j < 9; j += 3) {
        res = gridValidator_(board, i, j);
        if (!res)
          return false;
      }
    }

    return true;
  }
};
