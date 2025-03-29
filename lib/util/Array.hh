#include <algorithm>
#include <cstring>
#include <memory>
#include <vector>

#include "Random.hh"

struct Array
{
  /*
   * TODO: Make implementations for std::array
   */

private:
  Array();
  inline static Random &random_ = Random::get_instance();

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_partition_(std::unique_ptr<T[]> &A, std::ptrdiff_t p,
                                     std::ptrdiff_t r) -> std::ptrdiff_t
  {
    T x              = A[r];
    std::ptrdiff_t i = p - 1;

    for (std::ptrdiff_t j = p; j <= r - 1; j++)
    {
      if (A[j] <= x)
      {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_partition_(std::vector<T> &A, std::ptrdiff_t p,
                                     std::ptrdiff_t r) -> std::ptrdiff_t
  {
    T x              = A[r];
    std::ptrdiff_t i = p - 1;

    for (std::ptrdiff_t j = p; j <= r - 1; j++)
    {
      if (A[j] <= x)
      {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static auto randomized_partition_(std::unique_ptr<T[]> &A, std::ptrdiff_t p,
                                  std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t i =
        static_cast<std::ptrdiff_t>(random_.next_uniform_integer<int>(
            static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    return index_partition_(A, p, r);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static auto randomized_parition_(std::vector<T> &A, std::ptrdiff_t p,
                                  std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t i =
        static_cast<std::ptrdiff_t>(random_.next_uniform_integer<int>(
            static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    T pivot = A[r];
    auto it = std::partition(&A[p], &A[r],
                             [pivot](const T &val) { return val <= pivot; });

    std::iter_swap(it, &A[r]);
    return std::distance(&A[p], it);
  }

  template <typename T>
  inline static auto lomuto_partition_(std::unique_ptr<T[]> &nums,
                                      std::ptrdiff_t p, std::ptrdiff_t r)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r])
      std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r])
      std::swap(nums[p + 1], nums[r]);
    if (nums[p] < nums[p + 1])
      std::swap(nums[p], nums[p + 1]);

    T pivot          = nums[p + 1];
    std::ptrdiff_t i = p + 1, j = r;

    while (true)
    {
      while (nums[++i] > pivot)
        continue;
      while (nums[--j] < pivot)
        continue;
      if (i > j)
        break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

  template <typename T>
  inline static auto lomuto_partition_(std::vector<T> &nums, std::ptrdiff_t p,
                                      std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r])
      std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r])
      std::swap(nums[p + 1], nums[r]);
    if (nums[p] < nums[p + 1])
      std::swap(nums[p], nums[p + 1]);

    T pivot          = nums[p + 1];
    std::ptrdiff_t i = p + 1, j = r;

    while (true)
    {
      while (nums[++i] > pivot)
        continue;
      while (nums[--j] < pivot)
        continue;
      if (i > j)
        break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

public:
  inline static void integer_bucket_sort(std::unique_ptr<int[]> &array,
                                       std::size_t length)
  {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix, std::vector<int>(length));

    std::vector<int> size(radix);
    for (std::size_t i = 0; i < length; i++)
    {
      int e                         = array[i];
      int index                     = e & (radix - 1);
      buckets[index][size[index]++] = e;
    }

    std::vector<std::vector<int>> new_buckets(radix, std::vector<int>(length));
    for (unsigned int i = bits; i < sizeof(int) * 8; i += bits)
    {
      std::vector<int> new_size(radix);
      for (int j = 0; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
        {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          new_buckets[index][new_size[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, new_buckets);
      size = new_size;
    }

    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++)
      {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
    }
  }

  inline static void integer_bucket_sort(std::vector<int> &vector)
  {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix,
                                          std::vector<int>(vector.size()));

    std::vector<int> size(radix);
    for (int e : vector)
    {
      int index                     = e & (radix - 1);
      buckets[index][size[index]++] = e;
    }

    std::vector<std::vector<int>> new_buckets(radix,
                                             std::vector<int>(vector.size()));
    for (unsigned int i = bits; i < sizeof(int) * 8; i += bits)
    {
      std::vector<int> new_size(radix);
      for (int j = 0; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
        {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          new_buckets[index][new_size[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, new_buckets);
      size = new_size;
    }

    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++)
      {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void randomized_quick_sort(std::unique_ptr<T[]> &A,
                                     std::ptrdiff_t start,
                                     std::ptrdiff_t pastEnd)
  {
    while (start < pastEnd - 1)
    {
      std::ptrdiff_t q = randomized_partition_(A, start, pastEnd - 1);
      randomized_quick_sort(A, start, q);
      start = q + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void randomized_quick_sort(std::vector<T> &A, std::ptrdiff_t start,
                                     std::ptrdiff_t pastEnd)
  {
    while (start < pastEnd - 1)
    {
      std::ptrdiff_t q = randomized_partition_(A, start, pastEnd - 1);
      randomized_quick_sort(A, start, q);
      start = q + 1;
    }
  }

  inline static auto stable_counting_sort(std::unique_ptr<std::uint32_t[]> &A,
                                        std::size_t n, std::uint32_t max)
      -> std::unique_ptr<std::uint32_t[]>
  {
    std::unique_ptr<std::uint32_t[]> B(new std::uint32_t[n]),
        C(new std::uint32_t[max + 1]);
    std::memset(C.get(), 0x00, sizeof(int) * (max + 1));

    for (std::uint32_t j = 0; j < n; j++)
      C[A[j]]++;

    for (std::uint32_t i = 1; i <= max; i++)
      C[i] = C[i] + C[i - 1];

    for (std::ptrdiff_t j = n - 1; j >= 0; j--)
    {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  inline static auto stable_counting_sort(std::vector<std::uint32_t> &A,
                                        std::size_t n, std::uint32_t max)
      -> std::vector<std::uint32_t>
  {
    std::vector<std::uint32_t> B(n), C(max + 1, 0);

    for (std::uint32_t j = 0; j < n; j++)
      C[A[j]]++;

    for (std::uint32_t i = 1; i <= max; i++)
      C[i] = C[i] + C[i - 1];

    for (std::ptrdiff_t j = n - 1; j >= 0; j--)
    {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_binary_search(const std::unique_ptr<T[]> &a,
                                       std::ptrdiff_t start,
                                       std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i <= j)
    {
      std::ptrdiff_t m = (i + j) >> 1;
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
  inline static auto index_binary_search(const std::vector<T> &a,
                                       std::ptrdiff_t start,
                                       std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i <= j)
    {
      std::ptrdiff_t m = (i + j) >> 1;
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
  inline static auto index_ternary_search(const std::unique_ptr<T[]> &a,
                                        std::ptrdiff_t start,
                                        std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i < j - 1)
    {
      std::ptrdiff_t l = (i + j) / 3;
      std::ptrdiff_t u = ((i + j) / 3) << 1;

      if (key > a[u])
      {
        i = u + 1;
      }
      else if (key > a[l])
      {
        i = l + 1;
        j = u;
      }
      else
      {
        j = l;
      }
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
  inline static auto index_ternary_search(const std::vector<T> &a,
                                        std::ptrdiff_t start,
                                        std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i < j - 1)
    {
      std::ptrdiff_t l = (i + j) / 3;
      std::ptrdiff_t u = ((i + j) / 3) << 1;

      if (key > a[u])
      {
        i = u + 1;
      }
      else if (key > a[l])
      {
        i = l + 1;
        j = u;
      }
      else
      {
        j = l;
      }
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
  inline static auto inverse_order_statistic(std::unique_ptr<T[]> &A,
                                           std::ptrdiff_t start,
                                           std::ptrdiff_t pastEnd,
                                           std::size_t order) -> T
  {
    std::ptrdiff_t left = start, right = pastEnd - 1;

    while (true)
    {
      if (right <= left + 1)
      {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomuto_partition_(A, left, right);

      if (j >= order - 1)
        right = j - 1;
      if (j <= order - 1)
        left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto inverse_order_statistic(std::vector<T> &A,
                                           std::ptrdiff_t start,
                                           std::ptrdiff_t pastEnd,
                                           std::size_t order) -> T
  {
    std::ptrdiff_t left = start, right = pastEnd - 1;

    while (true)
    {
      if (right <= left + 1)
      {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomuto_partition_(A, left, right);

      if (j >= order - 1)
        right = j - 1;
      if (j <= order - 1)
        left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto order_statistic(std::unique_ptr<T[]> &A,
                                    std::ptrdiff_t start,
                                    std::ptrdiff_t pastEnd, std::size_t order)
      -> T
  {
    return inverse_order_statistic(A, start, pastEnd,
                                 pastEnd - start - order + 1);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto order_statistic(std::vector<T> &A, std::ptrdiff_t start,
                                    std::ptrdiff_t pastEnd, std::size_t order)
      -> T
  {
    return inverse_order_statistic(A, start, pastEnd,
                                 pastEnd - start - order + 1);
  }
};
