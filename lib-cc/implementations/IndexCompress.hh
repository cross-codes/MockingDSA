#include <algorithm>
#include <vector>

template <typename T> struct IndexCompress
{
private:
  std::vector<T> compressed_vals;

public:
  explicit IndexCompress(std::vector<T> &&vec) : compressed_vals(std::move(vec))
  {
    std::ranges::sort(compressed_vals);
    auto last = std::unique(compressed_vals.begin(), compressed_vals.end());
    compressed_vals.erase(last, compressed_vals.end());
  }

  std::size_t get_compressed_index(T value)
  {
    return std::lower_bound(compressed_vals.begin(), compressed_vals.end(),
                            value) -
           compressed_vals.begin();
  }

  std::size_t get_max_range()
  {
    return compressed_vals.size() - 1;
  }
};
