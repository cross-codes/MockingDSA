#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
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

namespace _PermutationOrder {

std::array<int64_t, 21> factorial{};

constexpr void precompute() {
  factorial[0] = 1;
  for (int i = 1; i < 21; i++) {
    factorial[i] = factorial[i - 1] * i;
  }
}

auto run() -> void {
  auto get_kth_permutation = [](int n, int64_t k) -> std::vector<int> {
    uint32_t used_msk{0x0001};
    auto unused = [&used_msk, &n](int ord) -> int {
      for (int i = 1; i <= n; i++) {
        if (!((used_msk >> i) & 1)) {
          ord -= 1;
          if (ord <= 0) {
            return i;
          }
        }
      }

      __builtin_unreachable();
    };

    std::vector<int> result{};
    for (int i = 0; i < n; i++) {
      int skip = static_cast<int>((k + factorial[n - i - 1] - 1) /
                                  factorial[n - i - 1]);
      result.push_back(unused(skip));
      used_msk |= 1 << (result.back());
      k -= (factorial[n - i - 1] * (skip - 1));
    }

    return result;
  };

  auto get_permutation_index = [](int n,
                                  const std::vector<int>& seq) -> int64_t {
    uint32_t used_msk{0x0001};
    auto unused = [&used_msk]() -> int { return __builtin_ffs(~used_msk); };

    auto ord    = [&used_msk](int pos) -> int {
      uint32_t lmsk = (1U << pos) - 1;
      return pos - std::popcount(used_msk & lmsk);
    };

    int64_t idx{};
    for (int i = 0; i < n; i++) {
      int target = unused() - 1;
      idx += (ord(seq[i]) - ord(target)) * factorial[n - i - 1];
      used_msk |= (1 << seq[i]);
    }

    return idx + 1;
  };

  int type;
  std::cin >> type;
  if (type == 1) {
    int n;
    int64_t k;
    std::cin >> n >> k;

    const auto& vec = get_kth_permutation(n, k);
    for (int e : vec) {
      std::cout << e << " ";
    }

    std::cout << "\n";
  } else {
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
      std::cin >> p[i];
    }

    std::cout << get_permutation_index(n, p) << "\n";
  }
}

}  // namespace _PermutationOrder

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

  _PermutationOrder::precompute();
  int t{1};
  std::cin >> t;
  while (t-- > 0)
    _PermutationOrder::run();

  std::cout.flush();

  return 0;
}
