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

namespace _Apartments {

auto run() -> void {
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  int cnt{}, applicant{}, house{};
  while (applicant < n && house < m) {
    while (applicant < n && a[applicant] < b[house] - k) {
      applicant += 1;
    }

    while (house < m && a[applicant] > b[house] + k) {
      house += 1;
    }

    if (house == m) {
      break;
    }

    if (a[applicant] >= b[house] - k) {
      cnt += 1;
      house += 1;
      applicant += 1;
    } else {
      applicant += 1;
    }
  }

  std::cout << cnt << "\n";
}

}  // namespace _Apartments

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
    _Apartments::run();

  std::cout.flush();

  return 0;
}
