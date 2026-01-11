#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <bitset>
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _GrayCode {

auto run() -> void {
  int n;
  std::cin >> n;

  for (int i = 0; i < (1 << n); i++) {
    int gray = i ^ (i >> 1);
    std::bitset<64> b(gray);
    std::string rep = b.to_string();
    std::cout << rep.substr(rep.size() - n, n) << "\n";
  }
}

}  // namespace _GrayCode

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _GrayCode::run();

  std::cout.flush();

  return 0;
}
