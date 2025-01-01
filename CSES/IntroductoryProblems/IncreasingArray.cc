#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t, target;
  std::cin >> t;
  std::cin >> target;

  u64 numMoves = 0ULL;
  for (int i = 1; i < t; i++) {
    int num;
    std::cin >> num;
    if (num < target) {
      numMoves += (target - num);
    } else
      target = num;
  }

  std::cout << numMoves << "\n";

  return 0;
}
