#include <algorithm>
#include <vector>

class WaveletTree {
 public:
  using Iterator = std::vector<int>::iterator;

  WaveletTree(Iterator from, Iterator to, int x, int y) {
    m_low = x, m_high = y;

    if (from >= to || m_low == m_high) {
      left = right = nullptr;
      return;
    }

    int mid   = m_low + (m_high - m_low) / 2;
    auto pred = [mid](int x) { return x <= mid; };

    m_pref_count.reserve(std::distance(from, to) + 1);
    m_pref_count.push_back(0);
    for (auto it = from; it != to; ++it) {
      m_pref_count.push_back(m_pref_count.back() + pred(*it));
    }

    auto pivot = std::stable_partition(from, to, pred);

    left       = new WaveletTree(from, pivot, m_low, mid);
    right      = new WaveletTree(pivot, to, mid + 1, m_high);
  }

  ~WaveletTree() {
    delete left;
    delete right;
  }

  int kth_smallest_one_indexed(int from, int excl_to, int k) {
    if (from >= excl_to)
      return -1;
    if (m_low == m_high)
      return m_low;

    int lb     = m_pref_count[from];
    int rb     = m_pref_count[excl_to];
    int inLeft = rb - lb;

    if (k <= inLeft) {
      return left->kth_smallest_one_indexed(lb, rb, k);
    } else {
      return right->kth_smallest_one_indexed(from - lb, excl_to - rb,
                                             k - inLeft);
    }
  }

  int num_leq(int from, int excl_to, int target) {
    if (from >= excl_to || target < m_low)
      return 0;
    if (m_high <= target)
      return excl_to - from;

    int lb = m_pref_count[from];
    int rb = m_pref_count[excl_to];
    return left->num_leq(lb, rb, target) +
           right->num_leq(from - lb, excl_to - rb, target);
  }

  int num_eq(int from, int excl_to, int target) {
    if (from >= excl_to || target < m_low || target > m_high)
      return 0;
    if (m_low == m_high)
      return excl_to - from;

    int mid = m_low + (m_high - m_low) / 2;
    int lb  = m_pref_count[from];
    int rb  = m_pref_count[excl_to];

    if (target <= mid) {
      return left->num_eq(lb, rb, target);
    } else {
      return right->num_eq(from - lb, excl_to - rb, target);
    }
  }

 private:
  int m_low, m_high;
  WaveletTree *left, *right;
  std::vector<int> m_pref_count;
};
