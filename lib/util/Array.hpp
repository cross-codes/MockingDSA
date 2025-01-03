#include <vector>

struct Array {
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
    for (int i = bits; i < sizeof(int) * 8; i += bits) {
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
                                         const int &fromIndex,
                                         const int &toIndex, const T &key)
      -> int {

    int low = fromIndex;
    int high = toIndex - 1;
    while (low <= high) {
      int mid = (low + high) >> 1;
      if (vec[mid] < key)
        low = mid + 1;
      else if (vec[mid] > key)
        high = mid - 1;
      else
        return mid;
    }

    return -(low + 1);
  }
};
