#include <string>
#include <vector>

class Solution {
public:
  std::vector<std::string> res{};

  void search(int nOpen, int nClosed, int n, std::string current) {
    if (nOpen == nClosed && nOpen == n) {
      res.push_back(current);
      return;
    }

    if (nOpen < n) {
      current += '(';
      search(nOpen + 1, nClosed, n, current);
      current.pop_back();
    }

    if (nClosed < nOpen) {
      current += ')';
      search(nOpen, nClosed + 1, n, current);
    }
  }

  std::vector<std::string> generateParenthesis(int n) {
    search(0, 0, n, "");
    return res;
  }
};
