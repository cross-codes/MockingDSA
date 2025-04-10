#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 longestLength = 1U, currentLength = 1U;
  std::string str;
  std::cin >> str;

  char current = str[0];
  for (u32 i = 1; i < str.length(); i++) {
    char c = str[i];
    if (c != current) {
      longestLength = std::max(longestLength, currentLength);
      current = c;
      currentLength = 1U;
    } else
      currentLength++;
  }

  std::cout << std::max(longestLength, currentLength) << "\n";

  return 0;
}
