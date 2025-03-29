#include <algorithm>
#include <vector>

template <typename T> struct IndexCompress
{
private:
  std::vector<T> compressed_values;

public:
  explicit IndexCompress(std::vector<T> &&vec)
      : compressed_values(std::move(vec))
  {
    std::ranges::sort(compressed_values);
    compressed_values.erase(
        std::unique(compressed_values.begin(), compressed_values.end()),
        compressed_values.end());
  }

  std::size_t get_comp_index(T value)
  {
    return std::lower_bound(compressed_values.begin(), compressed_values.end(),
                            value) -
           compressed_values.begin();
  }

  std::size_t get_max_range()
  {
    return compressed_values.size() - 1;
  }
};
