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

namespace _D {

// Off by one errors and MISREAD QUESTION
template <class T>
class MergeSortTree {
 public:
  MergeSortTree(int from, int excl_to, const std::vector<T>& e)
      : m_l(from), m_r(excl_to) {
    if (excl_to - from == 1) {
      m_v.push_back(e[from]);
      m_left = m_right = nullptr;
    } else {
      int mid = from + (excl_to - from) / 2;
      m_left  = new MergeSortTree(from, mid, e);
      m_right = new MergeSortTree(mid, excl_to, e);

      m_v.resize(excl_to - from);
      std::merge(m_left->m_v.begin(), m_left->m_v.end(), m_right->m_v.begin(),
                 m_right->m_v.end(), m_v.begin());
    }
  }

  ~MergeSortTree() {
    delete m_left;
    delete m_right;
  }

  auto count(int from, int excl_to, T range_incl_start, T range_incl_end)
      -> size_t {
    if (from >= m_r || excl_to <= m_l) {
      return 0;
    }

    if (m_l >= from && m_r <= excl_to) {
      auto it1 = std::lower_bound(m_v.begin(), m_v.end(), range_incl_start);
      auto it2 = std::upper_bound(m_v.begin(), m_v.end(), range_incl_end);
      return std::distance(it1, it2);
    }

    return m_left->count(from, excl_to, range_incl_start, range_incl_end) +
           m_right->count(from, excl_to, range_incl_start, range_incl_end);
  }

 private:
  int m_l, m_r;
  std::vector<T> m_v;
  MergeSortTree *m_left, *m_right;
};

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  MergeSortTree mst(0, n, a);

  int64_t inversions{};
  for (int i = 0; i < n; i++) {
    inversions += mst.count(i + 1, n, 1, a[i] - 1);
  }

  auto inv_xchg = [&](int l, int r) -> int64_t {
    int64_t inv = inversions;
    inv -= mst.count(l + 1, n, 1, a[l] - 1);
    // std::cout << inv << "\n";
    inv += mst.count(r + 1, n, 1, a[l] - 1);
    // std::cout << inv << "\n";
    inv += mst.count(l + 1, r + 1, a[l] + 1, 2001);
    // std::cout << inv << "\n";

    if (a[r] > a[l]) {
      inv += 1;
    }

    return inv;
  };

  int64_t best{inversions};
  int l_b{-1}, r_b{-1};
  for (int l = 0; l < n; l++) {
    for (int r = l + 1; r < n; r++) {
      int64_t x;
      if ((x = inv_xchg(l, r)) < best) {
        best = x;
        l_b  = l + 1;
        r_b  = r + 1;
      }
    }
  }

  if (l_b == -1) {
    std::cout << "1 1" << "\n";
  } else {
    std::cout << l_b << " " << r_b << "\n";
  }
}

}  // namespace _D

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
  std::cin >> t;
  while (t-- > 0)
    _D::run();

  std::cout.flush();

  return 0;
}
