#include <cstdint>
#include "../include/io.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <queue>

IO io;

#define cin ::io
#define cout ::io

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace part1 {
void run() {
  std::priority_queue<int, std::vector<int>, std::less<int>> heap1{};
  std::priority_queue<int, std::vector<int>, std::less<int>> heap2{};

  do {
    int x, y;
    cin >> x >> y;
    heap1.push(x);
    heap2.push(y);
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  u64 res = 0ULL;
  while (!heap1.empty()) {
    int a = heap1.top(), b = heap2.top();
    res += std::abs(a - b);
    heap1.pop(), heap2.pop();
  }

  cout << res << "\n";
}
} // namespace part1

namespace part2 {
void run() {
  __gnu_pbds::gp_hash_table<int, int> list1{};
  __gnu_pbds::gp_hash_table<int, int> list2{};

  do {
    int x, y;
    cin >> x >> y;
    list1[x] += 1;
    list2[y] += 1;
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  u64 similarityScore = 0ULL;
  for (auto pair : list1) {
    int key = pair.first, value = pair.second;
    similarityScore += key * value * list2[key];
  }

  cout << similarityScore << "\n";
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
