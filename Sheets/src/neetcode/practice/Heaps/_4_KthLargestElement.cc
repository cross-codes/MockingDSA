#include <algorithm>
#include <random>
#include <vector>

class Solution {
private:
  std::random_device randomDevice_;
  std::mt19937_64 engine_;

  template <typename T>
  inline auto indexPartition_(std::vector<T> &A, std::ptrdiff_t p,
                                     std::ptrdiff_t r) -> std::ptrdiff_t {
    T x = A[r];
    std::ptrdiff_t i = p - 1;

    for (std::ptrdiff_t j = p; j <= r - 1; j++) {
      if (A[j] <= x) {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  template <typename T>
  auto randomizedParition_(std::vector<T> &A, std::ptrdiff_t p,
                                       std::ptrdiff_t r) -> std::ptrdiff_t {
    std::uniform_int_distribution<int> distribution(static_cast<int>(p),
                                                    static_cast<int>(r));
    std::ptrdiff_t i = static_cast<std::ptrdiff_t>(distribution(engine_));
    std::swap(A[i], A[r]);

    return indexPartition_(A, p, r);
  }

  template <typename T>
  inline auto lomutoPartition_(std::vector<T> &nums, std::ptrdiff_t p,
                                      std::ptrdiff_t r) -> std::ptrdiff_t {
    std::ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r])
      std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r])
      std::swap(nums[p + 1], nums[r]);
    if (nums[p] < nums[p + 1])
      std::swap(nums[p], nums[p + 1]);

    T pivot = nums[p + 1];
    std::ptrdiff_t i = p + 1, j = r;

    while (true) {
      while (nums[++i] > pivot)
        ;
      while (nums[--j] < pivot)
        ;
      if (i > j)
        break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j] = pivot;
    return j;
  }

  template <typename T>
  inline auto inverseOrderStatistic_(std::vector<T> &A, std::ptrdiff_t start,
                                           std::ptrdiff_t pastEnd, std::size_t order)
      -> T {
    std::ptrdiff_t left = start, right = pastEnd - 1;

    while (true) {
      if (right <= left + 1) {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomutoPartition_(A, left, right);

      if (j >= order - 1)
        right = j - 1;
      if (j <= order - 1)
        left = j + 1;
    }
  }

public:
  Solution() : engine_(randomDevice_()) {}

  int findKthLargest(std::vector<int> &nums, int k) {
    return inverseOrderStatistic_(nums, 0, nums.size(), k);
  }
};
