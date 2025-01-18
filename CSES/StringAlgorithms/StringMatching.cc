#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>
#include <regex>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string input, regex;
  std::getline(std::cin, input);
  std::getline(std::cin, regex);

  std::regex sequence_regex(regex);

  auto match_begin =
      std::sregex_iterator(input.begin(), input.end(), sequence_regex);
  auto match_end = std::sregex_iterator();

  std::cout << std::distance(match_begin, match_end) << "\n";

  return 0;
}
