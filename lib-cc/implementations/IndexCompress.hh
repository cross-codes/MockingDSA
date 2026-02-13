#include <algorithm>
#include <vector>

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
