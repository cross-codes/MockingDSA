#include "../include/io.hpp"
#include <regex>

IO io;

#define cin ::io
#define cout ::io

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

namespace part1 {
std::regex pattern("mul\\(-?\\d+,-?\\d+\\)", std::regex_constants::ECMAScript);

void run() {
  i64 res = 0LL;
  do {
    std::string line;
    cin >> line;

    auto itBegin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto itEnd = std::sregex_iterator();
    for (std::sregex_iterator i = itBegin; i != itEnd; ++i) {
      std::smatch match = *i;
      std::string matchString = match.str();
      size_t loc = matchString.find(",", 0);

      i64 firstNumber = stoll(matchString.substr(4, loc - 4));
      i64 secondNumber =
          stoll(matchString.substr(loc + 1, matchString.size() - loc - 2));

      res += firstNumber * secondNumber;
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << res << "\n";
}
} // namespace part1

namespace part2 {
std::regex pattern("mul\\(-?\\d+,-?\\d+\\)|do\\(\\)|don't\\(\\)",
                   std::regex_constants::ECMAScript);

void run() {
  i64 res = 0LL;
  bool addResult = true;
  do {
    std::string line;
    cin >> line;

    auto itBegin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto itEnd = std::sregex_iterator();
    for (std::sregex_iterator i = itBegin; i != itEnd; ++i) {
      std::smatch match = *i;
      std::string matchString = match.str();
      if (matchString == "do()")
        addResult = true;
      else if (matchString == "don't()")
        addResult = false;
      else if (addResult) {
        size_t loc = matchString.find(",", 0);

        i64 firstNumber = stoll(matchString.substr(4, loc - 4));
        i64 secondNumber =
            stoll(matchString.substr(loc + 1, matchString.size() - loc - 2));

        res += firstNumber * secondNumber;
      }
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << res << "\n";
}
} // namespace part2

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Invalid args\n";
  } else if (strcmp(argv[1], "1") == 0) {
    part1::run();
  } else if (strcmp(argv[1], "2") == 0) {
    part2::run();
  } else {
    cout << "Invalid args\n";
  }
  return 0;
}
