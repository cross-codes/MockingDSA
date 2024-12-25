#include "../../include/BufferedIO.hpp"
#include <cstdint>
#include <cstring>
#include <queue>

namespace Part1 {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

BufferedIO::StandardInputReader in;
BufferedIO::StandardOutputWriter out;

void run() {
  std::priority_queue<i32> queue1{};
  std::priority_queue<i32> queue2{};

  i32 x, y;
  while (in.nextInt(x) && in.nextInt(y)) {
    queue1.push(x);
    queue2.push(y);
  }

  i64 distance = 0;
  while (!queue1.empty()) {
    distance += abs(queue1.top() - queue2.top());
    queue1.pop();
    queue2.pop();
  }

  out << distance << "\n";
}
} // namespace Part1

int32_t main() {
  Part1::run();
  return 0;
}