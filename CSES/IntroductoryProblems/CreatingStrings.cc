#include <algorithm>
#include <array>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr std::array<int, 9> precomputeFactorials() {
  std::array<int, 9> factorials = {1};
  for (int i = 1; i < 9; i++) {
    factorials[i] = factorials[i - 1] * i;
  }
  return factorials;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  constexpr auto factorials = precomputeFactorials();

  std::string input;
  std::cin >> input;

  std::array<int, 26> freq = {};
  for (char c : input)
    freq[c - 'a']++;

  i64 result = factorials[input.size()];

  for (int val : freq)
    result /= factorials[val];

  std::sort(input.begin(), input.end());

  std::cout << result << "\n";

  do {
    std::cout << input << "\n";
  } while (std::next_permutation(input.begin(), input.end()));

  return 0;
}
