#include <array>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr int n = 8;

std::array<std::string, ::n> board;
std::array<int, ::n> column{};
std::array<int, (::n << 1) - 1> diag1{}, diag2{};
u32 count;

void search(int);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  for (int i = 0; i < ::n; i++)
    std::getline(std::cin, ::board[i]);

  ::search(0);

  std::cout << ::count << "\n";

  return 0;
}

void search(int y) {
  if (y == ::n) {
    ::count++;
    return;
  }

  for (int x = 0; x < ::n; x++) {
    if (column[x] || diag1[x + y] || diag2[x - y + ::n - 1] ||
        ::board[y][x] == '*')
      continue;

    column[x] = diag1[x + y] = diag2[x - y + ::n - 1] = 1;
    search(y + 1);
    column[x] = diag1[x + y] = diag2[x - y + ::n - 1] = 0;
  }
}
