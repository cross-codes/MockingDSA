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

template <typename T>
struct IndexCompress {
 public:
  explicit IndexCompress(std::vector<T>&& vec)
      : m_compressed_vals(std::move(vec)) {
    std::ranges::sort(m_compressed_vals);
    auto last = std::unique(m_compressed_vals.begin(), m_compressed_vals.end());
    m_compressed_vals.erase(last, m_compressed_vals.end());
  }

  std::size_t get_compressed_index(T value) {
    return std::lower_bound(m_compressed_vals.begin(), m_compressed_vals.end(),
                            value) -
           m_compressed_vals.begin();
  }

  std::size_t get_max_range() { return m_compressed_vals.size() - 1; }

 private:
  std::vector<T> m_compressed_vals;
};

class WaveletMatrix {
 public:
  WaveletMatrix(std::vector<int>& arr, int max_val) {
    int n = static_cast<int>(arr.size());

    m_levels =
        32 - std::countl_zero(static_cast<uint32_t>(std::max(1, max_val)));

    m_pref.assign(m_levels, std::vector<int>(n + 1, 0));
    m_zero_boundary.assign(m_levels, 0);

    std::vector<int> temp(n);

    for (int l = m_levels - 1; l >= 0; l--) {
      int bit   = 1 << l;
      int zeros = 0;

      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          zeros++;
        }
        m_pref[l][i + 1] = zeros;
      }

      m_zero_boundary[l] = zeros;

      int left_idx       = 0;
      int right_idx      = zeros;
      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          temp[left_idx++] = arr[i];
        } else {
          temp[right_idx++] = arr[i];
        }
      }

      arr = temp;
    }
  }

  int kth_smallest_one_indexed(int from, int excl_to, int k) {
    int ans = 0;
    for (int l = m_levels - 1; l >= 0; l--) {
      int zeros_in_left     = m_pref[l][from];
      int zeros_in_right    = m_pref[l][excl_to];
      int zeros_in_interval = zeros_in_right - zeros_in_left;

      if (k <= zeros_in_interval) {
        from    = zeros_in_left;
        excl_to = zeros_in_right;
      } else {
        from    = m_zero_boundary[l] + (from - zeros_in_left);
        excl_to = m_zero_boundary[l] + (excl_to - zeros_in_right);
        k -= zeros_in_interval;
        ans |= (1 << l);
      }
    }

    return ans;
  }

  int num_eq(int from, int excl_to, int target) {
    if (target < 0 || target >= (1LL << m_levels)) {
      return 0;
    }

    for (int l = m_levels - 1; l >= 0; l--) {
      int zeros_in_left  = m_pref[l][from];
      int zeros_in_right = m_pref[l][excl_to];

      if ((target & (1 << l)) == 0) {
        from    = zeros_in_left;
        excl_to = zeros_in_right;
      } else {
        from    = m_zero_boundary[l] + (from - zeros_in_left);
        excl_to = m_zero_boundary[l] + (excl_to - zeros_in_right);
      }

      if (from == excl_to) {
        return 0;
      }
    }

    return excl_to - from;
  }

  int num_leq(int from, int excl_to, int target) {
    if (target < 0) {
      return 0;
    }
    if (target >= (1LL << m_levels)) {
      return excl_to - from;
    }

    int count = 0;

    for (int l = m_levels - 1; l >= 0; l--) {
      int zeros_in_left     = m_pref[l][from];
      int zeros_in_right    = m_pref[l][excl_to];
      int zeros_in_interval = zeros_in_right - zeros_in_left;

      if ((target & (1 << l)) == 0) {
        from    = zeros_in_left;
        excl_to = zeros_in_right;
      } else {
        count += zeros_in_interval;
        from    = m_zero_boundary[l] + (from - zeros_in_left);
        excl_to = m_zero_boundary[l] + (excl_to - zeros_in_right);
      }

      if (from == excl_to) {
        return count;
      }
    }

    count += (excl_to - from);
    return count;
  }

  int count_in_range(int from, int excl_to, int min_val, int max_val) {
    if (from >= excl_to || min_val > max_val)
      return 0;

    int max_limit = (1 << m_levels) - 1;
    if (max_val > max_limit)
      max_val = max_limit;
    if (min_val < 0)
      min_val = 0;
    if (min_val > max_val)
      return 0;

    int target_min = min_val - 1;
    bool track_min = target_min >= 0;

    int count_max = 0, count_min = 0;
    int f_max = from, t_max = excl_to;
    int f_min = from, t_min = excl_to;

    for (int l = m_levels - 1; l >= 0; l--) {
      const auto& p = m_pref[l];
      int zb        = m_zero_boundary[l];
      int bit       = 1 << l;

      int zl_max    = p[f_max];
      int zr_max    = p[t_max];
      if ((max_val & bit) == 0) {
        f_max = zl_max;
        t_max = zr_max;
      } else {
        count_max += (zr_max - zl_max);
        f_max = zb + f_max - zl_max;
        t_max = zb + t_max - zr_max;
      }

      if (track_min) {
        int zl_min = p[f_min];
        int zr_min = p[t_min];
        if ((target_min & bit) == 0) {
          f_min = zl_min;
          t_min = zr_min;
        } else {
          count_min += (zr_min - zl_min);
          f_min = zb + f_min - zl_min;
          t_min = zb + t_min - zr_min;
        }
      }
    }

    count_max += (t_max - f_max);
    if (track_min) {
      count_min += (t_min - f_min);
    }

    return count_max - count_min;
  }

 private:
  int m_levels;
  std::vector<std::vector<int>> m_pref;
  std::vector<int> m_zero_boundary;
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  IndexCompress<int> compressor((std::vector<int>(x)));

  std::vector<int> x_c(n);
  for (int i = 0; i < n; i++) {
    x_c[i] = static_cast<int>(compressor.get_compressed_index(x[i]));
  }

  WaveletMatrix wmm(x_c, static_cast<int>(compressor.get_max_range()));

  for (int i = 0, a, b, c, d; i < q; i++) {
    std::cin >> a >> b >> c >> d;
    int comp_min = static_cast<int>(compressor.get_compressed_index(c));
    int comp_max = static_cast<int>(compressor.get_compressed_index(d + 1) - 1);

    std::cout << wmm.count_in_range(a - 1, b, comp_min, comp_max) << "\n";
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
