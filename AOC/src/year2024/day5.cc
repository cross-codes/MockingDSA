#include "../include/io.hpp"
#include <cstdint>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_set>
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

inline bool
    validSequence(std::vector<i64>,
                  __gnu_pbds::gp_hash_table<int, std::unordered_set<int>>);

void run() {
  __gnu_pbds::gp_hash_table<int, std::unordered_set<int>> pageBefore;
  i64 result = 0LL;
  do {
    std::string input;
    cin >> input;

    size_t pos;
    if (pos = input.find("|"), pos != std::string::npos) {
      i64 firstNum = stoll(input.substr(0, pos));
      i64 secondNum = stoll(input.substr(pos + 1, input.npos));
      pageBefore[firstNum].insert(secondNum);
    } else if (!input.empty()) {
      std::vector<std::string> sequence = ::split(input, ",");

      std::vector<i64> nums;
      for (std::string s : sequence)
        nums.push_back(stoll(s));

      if (validSequence(nums, pageBefore))
        result += nums[nums.size() / 2];
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << result << "\n";
}

inline bool
validSequence(std::vector<i64> v,
              __gnu_pbds::gp_hash_table<int, std::unordered_set<int>> m) {
  size_t n = v.size();

  for (auto i = 0; i < n; i++) {
    i64 page = v[i];
    std::unordered_set<int> inFront;

    auto it = m.find(page);
    if (it != m.end())
      inFront = it->second;
    else
      continue;

    for (auto j = 0; j < i; j++) {
      if (inFront.contains(v[j]))
        return false;
    }

    for (auto j = i + 1; j < n; j++) {
      if (!inFront.contains(v[j]))
        return false;
    }
  }

  return true;
}

} // namespace part1

namespace part2 {

inline bool validSequence(std::vector<i64>,
                          std::unordered_map<int, std::unordered_set<int>>);

struct Page {
  int pageNumber;

  Page(int num) : pageNumber(num) {}

  struct PageHash {
    size_t operator()(const Page &p) const {
      return std::hash<int>()(p.pageNumber);
    }
  };

  bool operator==(const Page &other) const {
    return this->pageNumber == other.pageNumber;
  }

  std::unordered_set<Page, PageHash> pagesInFront;

  bool operator<(const Page &other) const {
    if (this->pagesInFront.contains(other))
      return true;
    return false;
  }

  void addInFront(Page page) { this->pagesInFront.insert(page); }
};

void run() {
  std::unordered_map<int, Page, Page::PageHash> knownPages{};
  std::unordered_map<int, std::unordered_set<int>> pagesBefore{};

  u64 result = 0ULL;
  do {
    std::string input;
    cin >> input;

    size_t loc = input.find("|"), exec = input.find(",");
    if (loc != std::string::npos) {
      i64 firstNumber = stoll(input.substr(0, loc));
      i64 secondNumber = stoll(input.substr(loc + 1, input.size()));
      pagesBefore[firstNumber].insert(secondNumber);

      if (knownPages.contains(firstNumber)) {
        knownPages[firstNumber].addInFront(Page(secondNumber));
      } else {
        Page newPage = Page(firstNumber);
        newPage.addInFront(Page(secondNumber));
        knownPages[firstNumber] = newPage;
      }
    } else if (exec != std::string::npos) {
      std::vector<std::string> values = ::split(input, ",");
      std::vector<i64> nums;
      for (auto string : values)
        nums.push_back(stoll(string));

      if (!validSequence(nums, pagesBefore)) {
        std::vector<Page> pages;
        for (int pageNum : nums) {
          auto it = knownPages.find(pageNum);
          if (it != knownPages.end())
            pages.push_back(it->second);
          else
            pages.push_back(Page(pageNum));
        }

        std::sort(pages.begin(), pages.end());
        result += pages[pages.size() / 2].pageNumber;
      }
    }
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  cout << result << "\n";
}

inline bool validSequence(std::vector<i64> v,
                          std::unordered_map<int, std::unordered_set<int>> m) {
  size_t n = v.size();

  for (auto i = 0; i < n; i++) {
    i64 page = v[i];
    std::unordered_set<int> inFront;

    auto it = m.find(page);
    if (it != m.end())
      inFront = it->second;
    else
      continue;

    for (auto j = 0; j < i; j++) {
      if (inFront.contains(v[j]))
        return false;
    }

    for (auto j = i + 1; j < n; j++) {
      if (!inFront.contains(v[j]))
        return false;
    }
  }

  return true;
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
