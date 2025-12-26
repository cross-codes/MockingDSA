#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <unordered_map>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _DistinctValuesSubarrays {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  std::unordered_map<int, int> pos{};
  pos.reserve(200001);
  int64_t cnt{};
  int l = 0;
  for (int r = 0; r < n; r++) {
    if (pos.contains(x[r])) {
      int upto = pos[x[r]] + 1;
      for (; l < upto; l++) {
        pos.erase(x[r]);
      }
    }

    cnt += r - l + 1;
    pos[x[r]] = r;
  }

  std::cout << cnt << "\n";
}

}  // namespace _DistinctValuesSubarrays

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
    _DistinctValuesSubarrays::run();

  std::cout.flush();

  return 0;
}
