#include <vector>

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
