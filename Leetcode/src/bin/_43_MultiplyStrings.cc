#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

class Solution {
 public:
  std::string multiply(std::string num1, std::string num2) {
    if (num1 == "0" || num2 == "0")
      return "0";

    std::ptrdiff_t n1 = num1.size(), n2 = num2.size();
    if (n1 < n2) {
      std::swap(num1, num2);
      std::swap(n1, n2);
    }

    std::vector<std::vector<int>> rows{};

    for (std::ptrdiff_t i = n2 - 1; i >= 0; i--) {
      int num{num2[i] - '0'};
      int carry{}, digit{}, product{};
      std::vector<int> row{};
      for (std::ptrdiff_t j = 0; j < n2 - 1 - i; j++)
        row.push_back(0);
      for (std::ptrdiff_t j = n1 - 1; j > 0; j--) {
        digit   = num1[j] - '0';
        product = digit * num + carry;
        carry   = product / 10;

        row.push_back(product % 10);
      }

      digit   = num1[0] - '0';
      product = digit * num + carry;
      while (product != 0) {
        row.push_back(product % 10);
        product /= 10;
      }

      while (row.size() != static_cast<std::size_t>(n1 + n2)) {
        row.push_back(0);
      }

      rows.push_back(row);
    }

    std::size_t N = rows.size();
    std::string res;

    int sum{}, carry{};
    for (std::size_t x = 0; x < static_cast<std::size_t>(n1 + n2 - 1); x++) {
      for (std::size_t y = 0; y < N; y++)
        sum += rows[y][x];

      sum += carry;
      carry = sum / 10;
      res.push_back('0' + sum % 10);
      sum = 0;
    }

    for (std::size_t y = 0; y < N; y++)
      sum += rows[y][n1 + n2 - 1];

    sum += carry;

    while (sum != 0) {
      res.push_back('0' + sum % 10);
      sum /= 10;
    }

    return res | std::views::reverse | std::ranges::to<std::string>();
    ;
  }
};
