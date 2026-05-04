#include <set>

class MedianWindow {
 public:
  std::multiset<int> low, high;
  std::int64_t lower_sum{}, higher_sum{};

  MedianWindow(const std::vector<int>& array, std::size_t k)
      : m_array(array), m_current_begin(0), m_current_end(0), m_window_size(k) {
    if (k & 1)
      m_expected_low_size = (k >> 1) + 1, m_expected_high_size = k >> 1;
    else
      m_expected_low_size = m_expected_high_size = k >> 1;

    for (std::size_t i = 0; i < m_size; i++)
      m_array[i] = array[i];

    for (std::size_t i = 0; i < m_window_size; i++) {
      low.insert(m_array[i]);
      lower_sum += m_array[i];
    }

    balance_sets_();
  }

  int next_median() {
    if (m_current_end == 0) [[unlikely]] {
      m_current_end = m_window_size;
      return *low.rbegin();
    }

    int r = m_array[m_current_begin++];

    if (low.contains(r)) {
      auto it = low.find(r);
      lower_sum -= *it;
      low.erase(low.find(r));
    } else {
      auto it = high.find(r);
      higher_sum -= *it;
      high.erase(high.find(r));
    }

    int e = m_array[m_current_end++];
    if (!high.empty() && e > *high.begin()) {
      higher_sum += e;
      high.insert(e);
    } else {
      lower_sum += e;
      low.insert(e);
    }

    balance_sets_();
    return *low.rbegin();
  }

 private:
  std::vector<int> m_array;
  std::size_t m_current_begin, m_current_end;
  std::size_t m_size, m_window_size;
  std::size_t m_expected_low_size, m_expected_high_size;

  void balance_sets_() {
    while (low.size() < m_expected_low_size) {
      auto it = high.begin();
      low.insert(*it);
      lower_sum += *it;
      higher_sum -= *it;
      high.erase(it);
    }

    while (high.size() < m_expected_high_size) {
      auto it = --low.end();
      higher_sum += *it;
      high.insert(*it);
      lower_sum -= *it;
      low.erase(it);
    }
  }
};
