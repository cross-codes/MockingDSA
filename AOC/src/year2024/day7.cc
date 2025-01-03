#include "../include/io.hpp"
#include <bitset>
#include <cmath>
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

const char *ws = " \t\n\r\f\v";

inline std::string &rtrim(std::string &s, const char *t = ws) {
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}
inline std::string &ltrim(std::string &s, const char *t = ws) {
  s.erase(0, s.find_first_not_of(t));
  return s;
}

inline std::string &trim(std::string &s, const char *t = ws) {
  return ltrim(rtrim(s, t), t);
}

namespace part1 {
void run() {

  i64 total = 0ULL;
  do {
    std::string input;
    cin >> input;
    auto split = ::split(input, ":");
    i64 target = stoll(split[0]);

    std::vector<std::string> strs = ::split(::trim(split[1]), " ");
    std::vector<int> nums{};
    for (auto &str : strs)
      nums.push_back(stoi(str));

    int n = nums.size() - 1;
    for (int i = 0; i < 1 << n; i++) {
      std::bitset<32> bits(i);
      std::string permutation = bits.to_string().substr(32 - n);

      i64 result = nums[0];
      int idx = 1;
      for (char c : permutation) {
        if (c == '0')
          result = result + nums[idx];
        else if (c == '1')
          result = result * nums[idx];
        idx++;
      }

      if (result == target) {
        total += target;
        break;
      }
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << total << "\n";
}
} // namespace part1

namespace part2 {
void run() {
  i64 total = 0LL;

  do {
    std::string input;
    cin >> input;

    auto split = ::split(input, ":");
    i64 target = stoll(split[0]);

    std::vector<std::string> strs = ::split(::trim(split[1]), " ");
    std::vector<int> nums{};
    for (auto &str : strs)
      nums.push_back(stoi(str));

    int n = nums.size() - 1;

    for (int i = 0; i < std::pow(3, n); i++) {
      std::vector<int> permutation(n, 0);

      int num = i;

      for (int j = n - 1; j >= 0; j--) {
        permutation[j] = num % 3;
        num /= 3;
      }

      i64 result = nums[0];
      int idx = 1;
      for (int num : permutation) {
        if (num == 0)
          result += nums[idx];
        else if (num == 1)
          result *= nums[idx];
        else if (num == 2) {
          auto left = std::to_string(result);
          left += std::to_string(nums[idx]);
          result = stoll(left);
        }
        idx++;
      }

      if (result == target) {
        total += target;
        break;
      }
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << total << "\n";
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
};
