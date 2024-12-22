#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <queue>

#pragma float_control(precise, off)

using namespace std;
using namespace __gnu_pbds;

typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

namespace Part1 {

void run() {
  priority_queue<i32> queue1{};
  priority_queue<i32> queue2{};

  i32 x, y;
  while (cin >> x >> y) {
    queue1.push(x);
    queue2.push(y);
  }

  i64 distance = 0;
  while (!queue1.empty()) {
    distance += abs(queue1.top() - queue2.top());
    queue1.pop();
    queue2.pop();
  }

  cout << distance << "\n";
}

} // namespace Part1

i32 main(i32 argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Part1::run();
  return 0;
}