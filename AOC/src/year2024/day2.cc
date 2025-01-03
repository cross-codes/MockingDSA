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

constexpr inline std::vector<std::string> split(std::string s,
                                                std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

namespace part1 {

void run() {
  u64 numberOfSafeLevels = 0ULL;

  do {
    std::string s;
    cin >> s;
    std::vector<std::string> stream = ::split(s, " ");
    if (stream.size() == 1)
      continue;

    bool strictlyIncreasing = stoi(stream[0]) < stoi(stream[1]);
    bool incorrect = false;
    for (int i = 1; i < stream.size(); i++) {
      int first = stoi(stream[i - 1]), second = stoi(stream[i]);
      if (strictlyIncreasing) {
        if (second - first > 3 || second - first <= 0) {
          incorrect = true;
          break;
        }
      } else {
        if (first - second > 3 || first - second <= 0) {
          incorrect = true;
          break;
        }
      }
    }

    if (!incorrect) {
      numberOfSafeLevels++;
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << numberOfSafeLevels << "\n";
}
} // namespace part1

namespace part2 {

inline bool isValidStream(std::vector<std::string> stream, bool retryCheck) {
  int size = stream.size();
  if (size == 1)
    return true;

  bool strictlyIncreasing = stoi(stream[0]) < stoi(stream[1]);
  for (int i = 1; i < stream.size(); i++) {
    int first = stoi(stream[i - 1]), second = stoi(stream[i]);
    if (strictlyIncreasing) {
      if (second - first > 3 || second - first <= 0) {
        if (retryCheck) {
          std::vector<std::string> removeFirst = stream;
          removeFirst.erase(removeFirst.begin() + i - 1);

          std::vector<std::string> removeSecond = stream;
          removeSecond.erase(removeSecond.begin() + i);

          std::vector<std::string> removeBegin = stream;
          removeBegin.erase(removeBegin.begin());

          return isValidStream(removeFirst, false) ||
                 isValidStream(removeSecond, false) ||
                 isValidStream(removeBegin, false);
        } else
          return false;
      }
    } else {
      if (first - second > 3 || first - second <= 0) {
        if (retryCheck) {
          std::vector<std::string> removeFirst = stream;
          removeFirst.erase(removeFirst.begin() + i - 1);

          std::vector<std::string> removeSecond = stream;
          removeSecond.erase(removeSecond.begin() + i);

          std::vector<std::string> removeBegin = stream;
          removeBegin.erase(removeBegin.begin());

          return isValidStream(removeFirst, false) ||
                 isValidStream(removeSecond, false) ||
                 isValidStream(removeBegin, false);
        } else
          return false;
      }
    }
  }

  return true;
}

void run() {
  u64 numberOfSafeLevels = 0ULL;

  do {
    std::string s;
    cin >> s;
    std::vector<std::string> stream = ::split(s, " ");
    if (isValidStream(stream, true))
      numberOfSafeLevels++;
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << numberOfSafeLevels << "\n";
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
