#include "../include/io.hpp"
#include <cstdint>
#include <vector>

IO io;

#define cin ::io
#define cout ::io

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace part1 {

inline i64 right(const std::vector<std::string> &, const std::string &);
inline i64 down(const std::vector<std::string> &, const std::string &);
inline i64 upLeft(const std::vector<std::string> &, const std::string &);
inline i64 upRight(const std::vector<std::string> &, const std::string &);

void run() {
  std::vector<std::string> grid;
  do {
    std::string in;
    cin >> in;
    grid.push_back(in);
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  i64 total = 0LL;

  total += right(grid, "XMAS");
  total += right(grid, "SAMX");

  total += down(grid, "XMAS");
  total += down(grid, "SAMX");

  total += upLeft(grid, "XMAS");
  total += upLeft(grid, "SAMX");

  total += upRight(grid, "XMAS");
  total += upRight(grid, "SAMX");

  cout << total << "\n";
}

inline i64 right(const std::vector<std::string> &v, const std::string &s) {
  i64 occurences = 0LL;

  int rowLength = v[0].size();
  int colLength = v.size();
  int patternLength = s.size();

  for (int i = 0; i < colLength; i++) {
    for (int j = 0; j <= rowLength - patternLength; j++) {
      bool incorrect = false;
      if (v[i][j] == s[0]) {
        for (int k = 1; k < patternLength; k++) {
          if (v[i][j + k] != s[k]) {
            incorrect = true;
            break;
          }
        }
        if (!incorrect)
          occurences++;
      }
    }
  }

  return occurences;
}

inline i64 down(const std::vector<std::string> &v, const std::string &s) {
  i64 occurences = 0LL;

  int rowLength = v[0].size();
  int colLength = v.size();
  int patternLength = s.size();

  for (int i = 0; i <= colLength - patternLength; i++) {
    for (int j = 0; j < rowLength; j++) {
      bool incorrect = false;
      if (v[i][j] == s[0]) {
        for (int k = 1; k < patternLength; k++) {
          if (v[i + k][j] != s[k]) {
            incorrect = true;
            break;
          }
        }
        if (!incorrect)
          occurences++;
      }
    }
  }

  return occurences;
}

inline i64 upLeft(const std::vector<std::string> &v, const std::string &s) {
  i64 occurences = 0LL;

  int rowLength = v[0].size();
  int colLength = v.size();
  int patternLength = s.size();

  for (int i = patternLength - 1; i < colLength; i++) {
    for (int j = patternLength - 1; j < rowLength; j++) {
      bool incorrect = false;
      if (v[i][j] == s[0]) {
        for (int k = 1; k < patternLength; k++) {
          if (v[i - k][j - k] != s[k]) {
            incorrect = true;
            break;
          }
        }
        if (!incorrect)
          occurences++;
      }
    }
  }

  return occurences;
}

inline i64 upRight(const std::vector<std::string> &v, const std::string &s) {
  i64 occurences = 0LL;

  int rowLength = v[0].size();
  int colLength = v.size();
  int patternLength = s.size();

  for (int i = patternLength - 1; i < colLength; i++) {
    for (int j = 0; j <= rowLength - patternLength; j++) {
      bool incorrect = false;
      if (v[i][j] == s[0]) {
        for (int k = 1; k < patternLength; k++) {
          if (v[i - k][j + k] != s[k]) {
            incorrect = true;
            break;
          }
        }
        if (!incorrect)
          occurences++;
      }
    }
  }

  return occurences;
}
} // namespace part1

namespace part2 {

inline i64 XPattern(const std::vector<std::string> &, const std::string &,
                    const std::string &);

void run() {
  std::vector<std::string> grid;
  do {
    std::string in;
    cin >> in;
    grid.push_back(in);
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  i64 occurences = 0ULL;

  occurences += XPattern(grid, "MAS", "SAM");
  occurences += XPattern(grid, "MAS", "MAS");
  occurences += XPattern(grid, "SAM", "SAM");
  occurences += XPattern(grid, "SAM", "MAS");

  cout << occurences << "\n";
}

inline i64 XPattern(const std::vector<std::string> &v, const std::string &s1,
                    const std::string &s2) {

  i64 occurences = 0LL;
  int rowLength = v[0].size();
  int colLength = v.size();
  int patternLengths = s1.length();

  for (int i = patternLengths - 1; i < colLength; i++) {
    for (int j = 0; j <= rowLength - patternLengths; j++) {
      bool incorrect = false;
      if (v[i][j] == s1[0] && v[i][j + 2] == s2[0]) {
        for (int k = 1; k < patternLengths; k++) {
          if (v[i - k][j + k] != s1[k]) {
            incorrect = true;
            break;
          }
        }
        if (!incorrect) {
          for (int k = 1; k < patternLengths; k++) {
            if (v[i - k][j + 2 - k] != s2[k]) {
              incorrect = true;
              break;
            }
          }
          if (!incorrect)
            occurences++;
        }
      }
    }
  }

  return occurences;
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
