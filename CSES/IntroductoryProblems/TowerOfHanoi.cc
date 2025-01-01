#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void move(int n, int from, int to, int via) {
  if (n == 0)
    return;
  move(n - 1, from, via, to);
  std::cout << from << " " << to << "\n";
  move(n - 1, via, to, from);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cout << (1 << n) - 1 << "\n";

  ::move(n, 1, 3, 2);

  return 0;
}
