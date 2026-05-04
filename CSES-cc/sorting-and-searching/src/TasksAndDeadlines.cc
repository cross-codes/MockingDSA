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

namespace _TasksAndDeadlines {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> tasks(n);
  for (int i = 0; i < n; i++) {
    std::cin >> tasks[i].first >> tasks[i].second;
  }

  std::sort(tasks.begin(), tasks.end());
  int64_t f = 0, reward = 0;
  for (const auto& [a, d] : tasks) {
    f += a;
    reward += d - f;
  }

  std::cout << reward << "\n";
}

}  // namespace _TasksAndDeadlines

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
    _TasksAndDeadlines::run();

  std::cout.flush();

  return 0;
}
