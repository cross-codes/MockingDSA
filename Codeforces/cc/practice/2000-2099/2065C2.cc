#include <bits/stdc++.h>

#ifdef ANTUMBRA
#include "extras/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64   = int64_t;
using u64   = uint64_t;
using u32   = uint32_t;
using u128  = unsigned __int128;

namespace _2065C2 {

struct Random {
  /*
   * Author: github.com/cross-codes
   */

 private:
  std::random_device randomDevice_;
  std::mt19937_64 engine_;

  Random() : engine_(randomDevice_()) {}
  Random(const Random &)            = delete;
  Random &operator=(const Random &) = delete;

 public:
  static Random &getInstance() {
    static Random instance;
    return instance;
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextUniformRandomInteger(T p, T r) {
    std::uniform_int_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextUniformRandomReal(T p, T r) {
    std::uniform_real_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextNormalReal(T p, T r) {
    std::normal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline bool nextBernoulli() {
    std::bernoulli_distribution distribution;
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextBinomialReal(T p, T r) {
    std::binomial_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextPoissonReal(T p, T r) {
    std::poisson_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextExponentialReal(T p, T r) {
    std::exponential_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextGammaReal(T p, T r) {
    std::gamma_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextWeibullReal(T p, T r) {
    std::weibull_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextLogNormalReal(T p, T r) {
    std::lognormal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextChiSquaredReal(T p, T r) {
    std::chi_squared_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextCauchyReal(T p, T r) {
    std::cauchy_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextTDistributionReal(T p, T r) {
    std::student_t_distribution<T> distribution(p, r);
    return distribution(engine_);
  }
};

struct Array {
  /*
   * Author: github.com/cross-codes
   */

 private:
  Array();
  inline static Random &random_ = Random::getInstance();

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto indexPartition_(const std::unique_ptr<T[]> &A, ptrdiff_t p,
                                     ptrdiff_t r) -> ptrdiff_t {
    T x         = A[r];
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

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto indexPartition_(const std::vector<T> &A, ptrdiff_t p,
                                     ptrdiff_t r) -> ptrdiff_t {
    T x         = A[r];
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

  template <typename T>
    requires std::three_way_comparable<T>
  static ptrdiff_t randomizedParition_(const std::unique_ptr<T[]> &A,
                                       ptrdiff_t p, ptrdiff_t r) {
    ptrdiff_t i = static_cast<ptrdiff_t>(random_.nextUniformRandomInteger<int>(
        static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    return indexPartition_(A, p, r);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static ptrdiff_t randomizedParition_(const std::vector<T> &A, ptrdiff_t p,
                                       ptrdiff_t r) {
    ptrdiff_t i = static_cast<ptrdiff_t>(random_.nextUniformRandomInteger<int>(
        static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    T pivot = A[r];
    auto it = std::partition(&A[p], &A[r],
                             [pivot](const T &val) { return val <= pivot; });

    std::iter_swap(it, &A[r]);
    return std::distance(&A[p], it);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto lomutoPartition_(const std::unique_ptr<T[]> &nums,
                                      ptrdiff_t p, ptrdiff_t r) -> T {
    ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r]) std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r - 1]) std::swap(nums[p + 1], nums[r - 1]);
    if (nums[p] < nums[p + 1]) std::swap(nums[p], nums[p + 1]);

    ptrdiff_t pivot = nums[p + 1];
    ptrdiff_t i = p + 1, j = r - 1;

    while (true) {
      while (nums[++i] > pivot);
      while (nums[--j] < pivot);
      if (i > j) break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto lomutoPartition_(std::vector<T> &nums, ptrdiff_t p,
                                      ptrdiff_t r) -> T {
    ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r]) std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r - 1]) std::swap(nums[p + 1], nums[r - 1]);
    if (nums[p] < nums[p + 1]) std::swap(nums[p], nums[p + 1]);

    ptrdiff_t pivot = nums[p + 1];
    ptrdiff_t i = p + 1, j = r - 1;

    while (true) {
      while (nums[++i] > pivot);
      while (nums[--j] < pivot);
      if (i > j) break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

 public:
  inline static void integerBucketSort(std::unique_ptr<int[]> &array,
                                       std::size_t length) {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix, std::vector<int>(length));

    std::vector<int> size(radix);
    for (std::size_t i = 0; i < length; i++) {
      int e                         = array[i];
      int index                     = e & radix - 1;
      buckets[index][size[index]++] = e;
    }

    std::vector<std::vector<int>> newBuckets(radix, std::vector<int>(length));
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
        for (int k = 0; k < size[j]; k++) array[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++) {
        for (int k = 0; k < size[j]; k++) array[i++] = buckets[j][k];
      }
    }
  }

  inline static void integerBucketSort(std::vector<int> &vector) {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix,
                                          std::vector<int>(vector.size()));

    std::vector<int> size(radix);
    for (int e : vector) {
      int index                     = e & radix - 1;
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
        for (int k = 0; k < size[j]; k++) vector[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++) {
        for (int k = 0; k < size[j]; k++) vector[i++] = buckets[j][k];
      }
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void TRERandomizedQuickSort(std::unique_ptr<T[]> &A, ptrdiff_t start,
                                     ptrdiff_t pastEnd) {
    while (start < pastEnd - 1) {
      ptrdiff_t q = randomizedParition_(A, start, pastEnd - 1);
      TRERandomizedQuickSort(A, start, q);
      start = q + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void TRERandomizedQuickSort(std::vector<T> &A, ptrdiff_t start,
                                     ptrdiff_t pastEnd) {
    while (start < pastEnd - 1) {
      ptrdiff_t q = randomizedParition_(A, start, pastEnd - 1);
      TRERandomizedQuickSort(A, start, q);
      start = q + 1;
    }
  }

  inline static auto stableCountingSort(std::unique_ptr<uint32_t[]> &A,
                                        std::size_t n, uint32_t max)
      -> std::unique_ptr<uint32_t[]> {
    std::unique_ptr<uint32_t[]> B(new uint32_t[n]), C(new uint32_t[max + 1]);
    std::memset(C.get(), 0x00, sizeof(int) * (max + 1));

    for (uint32_t j = 0; j < n; j++) C[A[j]]++;

    for (uint32_t i = 1; i <= max; i++) C[i] = C[i] + C[i - 1];

    for (ptrdiff_t j = n - 1; j >= 0; j--) {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  inline static auto stableCountingSort(std::vector<uint32_t> &A, std::size_t n,
                                        uint32_t max) -> std::vector<uint32_t> {
    std::vector<uint32_t> B(n), C(max + 1, 0);

    for (uint32_t j = 0; j < n; j++) C[A[j]]++;

    for (uint32_t i = 1; i <= max; i++) C[i] = C[i] + C[i - 1];

    for (ptrdiff_t j = n - 1; j >= 0; j--) {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  template <typename T>
    requires std::three_way_comparable<T>
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
    requires std::three_way_comparable<T>
  inline static auto indexBinarySearch(const std::vector<T> &a, ptrdiff_t start,
                                       ptrdiff_t pastEnd, const T &key)
      -> ptrdiff_t {
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
    requires std::three_way_comparable<T>
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

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto indexTernarySearch(const std::vector<T> &a,
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

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto inverseOrderStatistic(std::unique_ptr<T[]> &A,
                                           ptrdiff_t start, ptrdiff_t pastEnd,
                                           std::size_t order) -> T {
    ptrdiff_t left = start, right = pastEnd - 1;

    while (true) {
      if (right <= left + 1) {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomutoPartition_(A, left, right);

      if (j >= order - 1) right = j - 1;
      if (j <= order - 1) left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto inverseOrderStatistic(std::vector<T> &A, ptrdiff_t start,
                                           ptrdiff_t pastEnd, std::size_t order)
      -> T {
    ptrdiff_t left = start, right = pastEnd - 1;

    while (true) {
      if (right <= left + 1) {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomutoPartition_(A, left, right);

      if (j >= order - 1) right = j - 1;
      if (j <= order - 1) left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto orderStatistic(std::unique_ptr<T[]> &A, ptrdiff_t start,
                                    ptrdiff_t pastEnd, std::size_t order) -> T {
    return inverseOrderStatistic(A, start, pastEnd, pastEnd - start - order);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto orderStatistic(std::vector<T> &A, ptrdiff_t start,
                                    ptrdiff_t pastEnd, std::size_t order) -> T {
    return inverseOrderStatistic(A, start, pastEnd, pastEnd - start - order);
  }
};

auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::unique_ptr<int[]> a(new int[n]), b(new int[m]);

  for (ssize i = 0; i < n; i++) std::cin >> a[i];

  for (ssize i = 0; i < m; i++) std::cin >> b[i];

  Array::TRERandomizedQuickSort(b, 0, m);

  if (b[0] - a[0] < a[0]) a[0] = b[0] - a[0];

  for (ssize i = 1; i < n - 1; i++) {
    auto it = std::lower_bound(&b[0], &b[m], a[i] + a[i - 1]);
    if (it == &b[m]) [[unlikely]]
      continue;

    if (a[i] >= a[i - 1]) {
      if (*it - a[i] < a[i]) a[i] = *it - a[i];
    } else {
      a[i] = *it - a[i];
    }
  }

  if (b[m - 1] - a[n - 1] > a[n - 1]) a[n - 1] = b[m - 1] - a[n - 1];

  for (ssize i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      std::println("NO");
      return;
    }
  }

  std::println("YES");
}

}  // namespace _2065C2

int main() {
#ifdef ANTUMBRA
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

  while (t-- > 0) _2065C2::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
