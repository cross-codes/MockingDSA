#include <cstdint>
#include <iostream>
#include <sstream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;

  switch (n) {
  case 1:
  case 2:
    std::cout << "NO\n";
    break;

  case 3:
    std::cout << "YES\n2\n1 2\n1\n3\n";
    break;

  case 4:
    std::cout << "YES\n2\n1 4\n2\n2 3\n";
    break;

  default:
    if ((n - 3) % 4 == 0) {
      std::cout << "YES\n";

      std::stringstream row1, row2;
      row1 << "1 2 ";
      row2 << "3 ";
      u32 x = 4U, y = n, row1len = 2U, row2len = 1U;
      while (x < y) {
        row1 << x << " " << y << " ";
        x++;
        y--;
        row1len += 2U;
        if (x < y)
          row2 << x << " " << y << " ";
        x++;
        y--;
        row2len += 2U;
      }

      row1 << "\n";
      row2 << "\n";
      std::cout << row1len << "\n"
                << row1.str() << row2len << "\n"
                << row2.str();

    } else if (n % 4 == 0) {
      std::cout << "YES\n";

      std::stringstream row1, row2;
      u32 x = 1U, y = n, row1len = 0U, row2len = 0U;
      while (x < y) {
        row1 << x << " " << y << " ";
        x++;
        y--;
        row1len += 2U;
        if (x < y)
          row2 << x << " " << y << " ";
        x++;
        y--;
        row2len += 2U;
      }

      row1 << "\n";
      row2 << "\n";
      std::cout << row1len << "\n"
                << row1.str() << row2len << "\n"
                << row2.str();

    } else [[unlikely]]
      std::cout << "NO\n";

    break;
  }

  return 0;
}
