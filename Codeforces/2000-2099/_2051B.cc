#include <cstdint>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

// clang-format off

#if !defined(CROSS_DEBUG)
  #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
  #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,lzcnt,mmx,abm,avx,avx2,tune=native")
#else
  #pragma float_control(precise, off)
#endif

// clang-format on

namespace _2051B {

using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

void run() {
  i32 t;
  std::cin >> t;
  while (t-- > 0) {
    i64 n, a, b, c;
    std::cin >> n >> a >> b >> c;
    i64 k = n / (a + b + c), r = n % (a + b + c);

    i64 res = 3 * k;
    if (r > 0)
      res++;
    if (r - a > 0)
      res++;
    if (r - a - b > 0)
      res++;

    std::cout << res << "\n";
  }
}

} // namespace _2051B

int main(int argc, char **argv) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  _2051B::run();
  return 0;
}