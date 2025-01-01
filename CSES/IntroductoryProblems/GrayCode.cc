#include <bitset>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr int max_n = 16;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, numEntries;
  std::cin >> n, numEntries = 1 << n;

  for (int i = 0; i < numEntries; i++)
    std::cout << std::bitset<max_n>(i ^ (i >> 1)).to_string().substr(max_n - n)
              << "\n";

  return 0;
}
