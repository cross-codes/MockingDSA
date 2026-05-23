#include <chrono>
#include <cstdint>
#include <unordered_map>
#include <vector>

struct HasherFunctor
{
private:
  static std::uint64_t randomAddress()
  {
    char *p = new char;
    delete p;
    return std::uint64_t(p);
  }

  static std::uint32_t hash32(std::uint32_t x)
  {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static std::uint64_t splitmix64(std::uint64_t x)
  {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> std::uint64_t operator()(T x) const
  {
    static const std::uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

class Solution
{
public:
  std::vector<int> solveQueries(const std::vector<int> &nums,
                                const std::vector<int> &queries)
  {
    std::unordered_map<int, std::vector<int>, HasherFunctor> elemToIndex{};
    int n = static_cast<int>(nums.size());

    for (int i = 0UZ; i < n; i++)
      elemToIndex[nums[i]].push_back(static_cast<int>(i));

    std::vector<int> nearest(n, -1);

    for (const auto &[element, indices] : elemToIndex)
    {
      int m = static_cast<int>(indices.size());
      if (m == 1)
        continue;

      for (int i = 0; i < m; i++)
      {
        int index{indices[i]}, nextIndex{indices[(i + 1) % m]},
            prevIndex{indices[(i == 0) ? m - 1 : i - 1]};

        if (prevIndex < index && index < nextIndex)
          nearest[index] = std::min(nextIndex - index, index - prevIndex);
        else if (index < prevIndex)
          nearest[index] = std::min(nextIndex - index, n - prevIndex + index);
        else
          nearest[index] = std::min(n - index + nextIndex, index - prevIndex);
      }
    }

    int N = static_cast<int>(queries.size());
    std::vector<int> replies(N);
    for (int i = 0; i < N; i++)
      replies[i] = nearest[queries[i]];

    return replies;
  }
};
