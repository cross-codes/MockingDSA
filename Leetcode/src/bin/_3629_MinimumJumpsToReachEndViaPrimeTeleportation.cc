#include <array>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  int minJumps(std::vector<int> &nums)
  {
    static std::array<int, 1000001> sieve{};
    sieve[0]        = 1;
    sieve[1]        = 1;

    auto precompute = []() -> void {
      for (int i = 2; i < 1000001; i++)
      {
        if (sieve[i] > 0)
          continue;
        else
        {
          for (int u = (i << 1); u < 1000001; u += i)
            sieve[u] = i;
        }
      }
    };

    if (sieve[4] == 0)
      precompute();


    std::unordered_map<int, std::unordered_set<int>> prime_p{};
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; i++)
    {
      int x = nums[i];
      while (x > 1 && sieve[x] > 0)
      {
        prime_p[sieve[x]].insert(i);
        x /= sieve[x];
      }

      prime_p[x].insert(i);
    }

    std::bitset<100001> visited{};

    std::queue<std::pair<int, int>> queue{}; // pos, d
    queue.emplace(0, 0);
    visited[0] = true;
    while (!queue.empty())
    {
      auto [i, d] = queue.front();
      queue.pop();

      if (i >= n || i < 0)
        continue;

      if (i == n - 1)
        return d;

      if (i + 1 < n && !visited[i + 1])
      {
        queue.emplace(i + 1, d + 1);
        visited[i + 1] = true;
      }
      if (i - 1 >= 0 && !visited[i - 1])
      {
        queue.emplace(i - 1, d + 1);
        visited[i - 1] = true;
      }

      if (sieve[nums[i]] == 0)
      {
        auto &s = prime_p[nums[i]];
        for (int p : s)
        {
          if (p == i)
            continue;
          if (!visited[p])
          {
            queue.emplace(p, d + 1);
            visited[p] = true;
          }
        }

        s.clear();
      }
    }

    __builtin_unreachable();
  }
};

int main()
{
  std::vector<int> nums = {1, 2, 4, 6};
  Solution().minJumps(nums);
}
