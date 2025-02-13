#include <concepts>
#include <cstring>
#include <memory>
#include <vector>

#include "Random.hh"

template <typename T>
concept RAIterator = std::random_access_iterator<T>;

struct Array {

  /*
   * Author: Akshaj Rao (cross-codes)
   */

private:
  Array();
  inline static Random &random_ = Random::getInstance();

  inline static ptrdiff_t partition_(std::unique_ptr<int[]> &A, ptrdiff_t p,
                                     ptrdiff_t r) {
    int x = A[r];
    ptrdiff_t i = p - 1;

    for (ptrdiff_t j = p; j <= r - 1; j++) {
      if (A[j] <= x) {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  inline static ptrdiff_t partition_(std::unique_ptr<int64_t[]> &A, ptrdiff_t p,
                                     ptrdiff_t r) {
    int64_t x = A[r];
    ptrdiff_t i = p - 1;

    for (ptrdiff_t j = p; j <= r - 1; j++) {
      if (A[j] <= x) {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  static ptrdiff_t randomizedParition_(std::unique_ptr<int[]> &A, ptrdiff_t p,
                                       ptrdiff_t r) {
    ptrdiff_t i = static_cast<ptrdiff_t>(random_.nextUniformRandomInteger<int>(
        static_cast<int>(p), static_cast<int>(r)));

    std::swap(A[i], A[r]);
    return partition_(A, p, r);
  }

  static ptrdiff_t randomizedParition_(std::unique_ptr<int64_t[]> &A,
                                       ptrdiff_t p, ptrdiff_t r) {
    ptrdiff_t i = static_cast<ptrdiff_t>(random_.nextUniformRandomInteger<int>(
        static_cast<int>(p), static_cast<int>(r)));

    std::swap(A[i], A[r]);
    return partition_(A, p, r);
  }

public:
  inline static void integerBucketSort(std::vector<int> &vector) {
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

  static void TRE_Quicksort(std::unique_ptr<int[]> &A, ptrdiff_t p,
                            ptrdiff_t r) {
    while (p < r) {
      ptrdiff_t q = randomizedParition_(A, p, r);
      TRE_Quicksort(A, p, q - 1);
      p = q + 1;
    }
  }

  static void TRE_Quicksort(std::unique_ptr<int64_t[]> &A, ptrdiff_t p,
                            ptrdiff_t r) {
    while (p < r) {
      ptrdiff_t q = randomizedParition_(A, p, r);
      TRE_Quicksort(A, p, q - 1);
      p = q + 1;
    }
  }

  inline static auto stableCountingSort(std::unique_ptr<uint32_t[]> &A,
                                        size_t n, uint32_t max)
      -> std::unique_ptr<uint32_t[]> {
    std::unique_ptr<uint32_t[]> B(new uint32_t[n]), C(new uint32_t[max + 1]);

    std::memset(C.get(), 0x00, sizeof(int) * (max + 1));

    for (uint32_t j = 0; j < n; j++)
      C[A[j]]++;

    for (uint32_t i = 1; i <= max; i++)
      C[i] = C[i] + C[i - 1];

    for (ptrdiff_t j = n - 1; j >= 0; j--) {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  template <RAIterator I, typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto indexBinarySearch(I start, I end, const T &key)
      -> ptrdiff_t {

    I low = start, high = end - 1;
    while (low < high) {
      I mid = start +
              ((std::distance(start, low) + std::distance(start, high)) >> 1);
      if (*mid < key)
        low = mid + 1;
      else if (*mid > key)
        high = mid;
      else
        return static_cast<ptrdiff_t>(std::distance(start, mid));
    }

    return -(static_cast<ptrdiff_t>(std::distance(start, low)) + 1);
  }

  template <RAIterator I, typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto indexTernarySearch(I start, I end, const T &key)
      -> ptrdiff_t {
    I low = start, high = end - 1;

    while (low < high - 1) {
      size_t lowPHigh = std::distance(start, low) + std::distance(start, high);
      I l = start + lowPHigh / 3;
      I u = start + ((lowPHigh / 3) << 1);

      if (key > *u)
        low = u + 1;
      else if (key > *l) {
        low = l + 1;
        high = u;
      } else
        high = l;
    }

    if (key == *low)
      return static_cast<ptrdiff_t>(std::distance(start, low));
    else if (key == *high)
      return static_cast<ptrdiff_t>(std::distance(start, high));
    else
      return -1;
  }
};
