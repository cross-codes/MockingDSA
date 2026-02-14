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

namespace _RangeIntervalQueries {

template <class T>
class MergeSortTree {
 public:
  MergeSortTree(const std::vector<T>& xs)
      : m_n(static_cast<int>(xs.size())), m_st(m_n << 1) {
    for (int i = 0; i < m_n; i++)
      m_st[i + m_n] = std::vector<T>({xs[i]});

    for (int i = m_n - 1; i > 0; i--) {
      m_st[i].resize(m_st[i << 1].size() + (m_st[i << 1 | 1].size()));
      merge(m_st[i << 1].begin(), m_st[i << 1].end(), m_st[i << 1 | 1].begin(),
            m_st[i << 1 | 1].end(), m_st[i].begin());
    }
  }

  auto in_range(int l, int r, T a, T b) -> int {
    int ans = 0;
    for (l += m_n, r += m_n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ans += count(l++, a, b);
      if (r & 1)
        ans += count(--r, a, b);
    }
    return ans;
  }

 private:
  int m_n;
  std::vector<std::vector<T>> m_st;

  auto count(int i, T a, T b) -> size_t {
    return upper_bound(m_st[i].begin(), m_st[i].end(), b) -
           lower_bound(m_st[i].begin(), m_st[i].end(), a);
  }
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  MergeSortTree mst(x);

  for (int i = 0, a, b, c, d; i < q; i++) {
    std::cin >> a >> b >> c >> d;
    std::cout << mst.in_range(a - 1, b, c, d) << "\n";
  }
}

}  // namespace _RangeIntervalQueries

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
    _RangeIntervalQueries::run();

  std::cout.flush();

  return 0;
}
