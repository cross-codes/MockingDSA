#include <vector>

struct Array {

  /*
   * Author: Akshaj Rao (cross-codes)
   */

private:
  Array();

public:
  inline static void sort(std::vector<int> &vector) {
    int bits = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix,
                                          std::vector<int>(vector.size()));
    std::vector<int> size(radix);
    for (int e : vector) {
      int index = e & radix - 1;
      buckets[index][size[index]++] = e;
    }
    std::vector<std::vector<int>> newBuckets(radix,
                                             std::vector<int>(vector.size()));
    for (unsigned int i = bits; i < sizeof(int) * 8; i += bits) {
      std::vector<int> newSize(radix);
      for (int j = 0; j < radix; j++) {
        for (int k = 0; k < size[j]; k++) {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          newBuckets[index][newSize[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, newBuckets);
      size = newSize;
    }
    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++) {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++) {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
    }
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto __JDK__binarySearch(const std::vector<T> &vec,
                                         const size_t &fromIndex,
                                         const size_t &toIndex, const T &key)
      -> int {

    size_t low = fromIndex, high = toIndex - 1;
    while (low < high) {
      size_t mid = (low + high) >> 1;
      if (vec[mid] < key)
        low = mid + 1;
      else if (vec[mid] > key)
        high = mid;
      else
        return static_cast<int>(mid);
    }

    return -(static_cast<int>(low) + 1);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto ternarySearch(const std::vector<T> &vec,
                                   const size_t &fromIndex,
                                   const size_t &toIndex, const T &key) -> int {
    size_t low = fromIndex, high = toIndex - 1;

    while (low < high - 1) {
      size_t l = (low + high) / 3;
      size_t u = ((low + high) / 3) << 1;

      if (key > vec[u])
        low = u + 1;
      else if (key > vec[l]) {
        low = l + 1;
        high = u;
      } else
        high = l;
    }

    if (key == vec[low])
      return static_cast<int>(low);
    else if (key == vec[high])
      return static_cast<int>(high);
    else
      return -1;
  }
};
