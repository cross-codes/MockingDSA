#include <bits/stdc++.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _2051D {

struct Random {

  /*
   * Author: Akshaj Rao (cross-codes)
   */

private:
  std::random_device randomDevice_;
  std::mt19937_64 engine_;

  Random() : engine_(randomDevice_()) {};
  Random(const Random &) = delete;
  Random &operator=(const Random &) = delete;

public:
  static Random &getInstance() {
    static Random instance;
    return instance;
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextUniformRandomInteger(T p, T r) {
    std::uniform_int_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextUniformRandomReal(T p, T r) {
    std::uniform_real_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextNormalReal(T p, T r) {
    std::normal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  bool nextBernoulli() {
    std::bernoulli_distribution distribution;
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextBinomialReal(T p, T r) {
    std::binomial_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextPoissonReal(T p, T r) {
    std::poisson_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextExponentialReal(T p, T r) {
    std::exponential_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextGammaReal(T p, T r) {
    std::gamma_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextWeibullReal(T p, T r) {
    std::weibull_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextLogNormalReal(T p, T r) {
    std::lognormal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextChiSquaredReal(T p, T r) {
    std::chi_squared_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextCauchyReal(T p, T r) {
    std::cauchy_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  T nextTDistributionReal(T p, T r) {
    std::student_t_distribution<T> distribution(p, r);
    return distribution(engine_);
  }
};

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

  static void TRE_Quicksort(std::unique_ptr<int[]> &A, ptrdiff_t start,
                            ptrdiff_t inclusiveEnd) {
    while (start < inclusiveEnd) {
      ptrdiff_t q = randomizedParition_(A, start, inclusiveEnd);
      TRE_Quicksort(A, start, q - 1);
      start = q + 1;
    }
  }

  static void TRE_Quicksort(std::unique_ptr<int64_t[]> &A, ptrdiff_t start,
                            ptrdiff_t inclusiveEnd) {
    while (start < inclusiveEnd) {
      ptrdiff_t q = randomizedParition_(A, start, inclusiveEnd);
      TRE_Quicksort(A, start, q - 1);
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

auto run() -> void {
  int n;
  std::cin >> n;
  i64 x, y;
  std::cin >> x >> y;

  std::unique_ptr<i64[]> nums(new i64[n]);

  i64 sum = 0LL;
  for (int i = 0; i < n; i++) {
    i64 num;
    std::cin >> num;
    nums[i] = num;
    sum += num;
  }

  std::sort(&nums[0], &nums[n]);

  i64 numberOfPairs = 0LL;
  for (int i = 0; i < n; i++) {
    i64 currDiff = sum - nums[i];
    i64 lowerBound = currDiff - y, upperBound = currDiff - x;
    ssize lowerIndex = Array::indexBinarySearch(nums, i + 1, n, lowerBound);

    if (lowerIndex < 0)
      lowerIndex = -(lowerIndex + 1);

    if (lowerIndex == n)
      continue;

    i64 refVal = nums[lowerIndex];

    for (ssize j = lowerIndex - 1; j > i; j--) {
      if (nums[j] == refVal)
        lowerIndex--;
      else
        break;
    }

    ssize upperIndex = Array::indexBinarySearch(nums, i + 1, n, upperBound);
    if (upperIndex < 0) {
      upperIndex = -(upperIndex + 1) - 1;
      if (upperIndex + 1 == lowerIndex)
        continue;
    }

    refVal = nums[upperIndex];

    for (ssize j = upperIndex + 1; j < n; j++) {
      if (nums[j] == refVal)
        upperIndex++;
      else
        break;
    }

    numberOfPairs += upperIndex - lowerIndex + 1;
  }

  std::println("{}", numberOfPairs);
}

} // namespace _2051D

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t;
  std::cin >> t;

  while (t-- > 0)
    _2051D::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
