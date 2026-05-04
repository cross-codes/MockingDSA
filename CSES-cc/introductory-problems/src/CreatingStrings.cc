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

namespace _CreatingStrings {

constexpr std::array<int, 9> FACTORIALS = {1,   1,   2,    6,    24,
                                           120, 720, 5040, 40320};

auto run() -> void {
  std::string str;
  std::cin >> str;

  std::array<int, 26> freq{};
  for (char e : str) {
    freq[e - 'a'] += 1;
  }

  int k = FACTORIALS[str.size()];
  for (int e : freq) {
    k /= FACTORIALS[e];
  }

  std::cout << k << "\n";

  std::sort(str.begin(), str.end());
  do {
    std::cout << str << "\n";
  } while (std::next_permutation(str.begin(), str.end()));
}

}  // namespace _CreatingStrings

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
    _CreatingStrings::run();

  std::cout.flush();

  return 0;
}
