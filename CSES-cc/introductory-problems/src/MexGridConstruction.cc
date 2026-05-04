#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <unordered_set>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _MexGridConstruction {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::unordered_set<int>> row_sets(n);
  std::vector<std::unordered_set<int>> col_sets(n);

  std::unordered_set<int> range{};
  for (int i = 0; i < 251; i++) {
    range.insert(i);
  }

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      std::unordered_set<int> difference = range;
      for (int e : row_sets[y]) {
        difference.erase(e);
      }

      for (int e : col_sets[x]) {
        difference.erase(e);
      }

      int min = *std::min_element(difference.begin(), difference.end());
      row_sets[y].insert(min);
      col_sets[x].insert(min);
      std::cout << min << " ";
    }

    std::cout << "\n";
  }
}

}  // namespace _MexGridConstruction

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
    _MexGridConstruction::run();

  std::cout.flush();

  return 0;
}
