#include <concepts>
#include <cstring>
#include <memory>
#include <vector>

#include "Random.hh"

struct Array {

  /*
   * Author: github.com/cross-codes
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

  static void TRERandomizedQuickSort(std::unique_ptr<int[]> &A, ptrdiff_t start,
                                     ptrdiff_t pastEnd) {
    while (start < pastEnd - 1) {
      ptrdiff_t q = randomizedParition_(A, start, pastEnd - 1);
      TRERandomizedQuickSort(A, start, q);
      start = q + 1;
    }
  }

  static void TRERandomizedQuickSort(std::unique_ptr<int64_t[]> &A,
                                     ptrdiff_t start, ptrdiff_t pastEnd) {
    while (start < pastEnd - 1) {
      ptrdiff_t q = randomizedParition_(A, start, pastEnd - 1);
      TRERandomizedQuickSort(A, start, q);
      start = q + 1;
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

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto indexBinarySearch(const std::unique_ptr<T[]> &a,
                                       ptrdiff_t start, ptrdiff_t pastEnd,
                                       const T &key) -> ptrdiff_t {
    ptrdiff_t i = start, j = pastEnd - 1;
    while (i <= j) {
      ptrdiff_t m = (i + j) >> 1;
      if (a[m] < key)
        i = m + 1;
      else if (a[m] > key)
        j = m - 1;
      else
        return m;
    }

    return -(i + 1);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static auto indexTernarySearch(const std::unique_ptr<T[]> &a,
                                        ptrdiff_t start, ptrdiff_t pastEnd,
                                        const T &key) -> ptrdiff_t {

    ptrdiff_t i = start, j = pastEnd - 1;
    while (i < j - 1) {
      ptrdiff_t l = (i + j) / 3;
      ptrdiff_t u = ((i + j) / 3) << 1;

      if (key > a[u])
        i = u + 1;
      else if (key > a[l]) {
        i = l + 1;
        j = u;
      } else
        j = l;
    }

    if (key == a[i])
      return i;
    else if (key == a[j])
      return j;
    else
      return -1;
  }
};
