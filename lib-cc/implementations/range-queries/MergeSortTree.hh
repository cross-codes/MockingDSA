#include <vector>

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
