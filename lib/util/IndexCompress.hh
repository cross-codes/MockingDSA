#include <algorithm>
#include <vector>

template <typename T> struct IndexCompress
{
private:
  std::vector<T> compressedValues;

public:
  explicit IndexCompress(std::vector<T> &&vec)
      : compressedValues(std::move(vec))
  {
    std::ranges::sort(compressedValues);
    compressedValues.erase(
        std::unique(compressedValues.begin(), compressedValues.end()),
        compressedValues.end());
  }

  std::size_t getCompressedIndex(T value)
  {
    return std::lower_bound(compressedValues.begin(), compressedValues.end(),
                            value) -
           compressedValues.begin();
  }

  std::size_t getMaxRange()
  {
    return compressedValues.size() - 1;
  }
};
