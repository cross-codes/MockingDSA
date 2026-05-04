#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <utility>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _Repetitions {

auto run() -> void {
  std::string str;
  std::cin >> str;

  char cur = str[0];
  int mx{1}, len{1};
  for (size_t i = 1; i < str.size(); i++) {
    if (str[i] == cur) {
      len += 1;
    } else {
      len = 1;
      cur = str[i];
    }

    mx = std::max(mx, len);
  }

  std::cout << mx << "\n";
}

}  // namespace _Repetitions

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
    _Repetitions::run();

  std::cout.flush();

  return 0;
}
