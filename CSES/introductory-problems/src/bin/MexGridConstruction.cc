#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <ranges>
#include <set>
#include <string>  // IWYU pragma: keep
#include <unordered_set>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _MexGridConstruction {

auto run() -> void {
  int n;
  std::cin >> n;

  std::set<int> model{};
  for (int i = 0; i <= 200; i++) {
    model.insert(i);
  }

  std::vector<std::set<int>> row_sets{}, col_sets{};
  for (int i = 0; i < 100; i++) {
    row_sets.push_back(std::set<int>(model));
    col_sets.push_back(std::set<int>(model));
  }

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      auto intersection =
          row_sets[y] | std::ranges::views::filter([&x, &col_sets](int i) {
            return col_sets[x].contains(i);
          });

      std::optional<int> mx{};
      if (!intersection.empty()) {
        mx = intersection.front();
      }

      if (mx.has_value()) {
        row_sets[y].erase(mx.value());
        col_sets[x].erase(mx.value());
        std::cout << mx.value() << " ";
      } else {
        __builtin_trap();
      }
    }

    std::cout << "\n";
  }
}

}  // namespace _MexGridConstruction

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef AZURELIGHT
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size) {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

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

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
