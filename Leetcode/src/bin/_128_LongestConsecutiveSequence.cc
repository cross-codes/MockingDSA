#include <unordered_map>
#include <vector>

class Solution
{
public:
  int longestConsecutive(std::vector<int> &nums)
  {
    if (nums.empty())
    {
      return 0;
    }

    std::unordered_map<int, int> v_id{};
    int gcnt{};
    for (int e : nums)
    {
      if (!v_id.contains(e))
      {
        v_id.insert({e, gcnt++});
      }
    }

    int n = static_cast<int>(v_id.size());
    std::vector<int> f(n, -1), p(n, -1);
    for (int e : nums)
    {
      int from_id = v_id[e];
      if (f[from_id] != -1)
      {
        continue;
      }

      if (v_id.contains(e + 1))
      {
        int to_id  = v_id[e + 1];
        f[from_id] = to_id;
      }

      if (v_id.contains(e - 1))
      {
        int to_id  = v_id[e - 1];
        p[from_id] = to_id;
      }
    }

    std::vector<bool> visited(n, false);
    auto dfs = [&visited, &f](auto &&dfs, int u) -> int {
      visited[u] = true;
      if (f[u] != -1 && !visited[f[u]])
      {
        return 1 + dfs(dfs, f[u]);
      }

      return 1;
    };

    int mx{-1};
    for (int id = 0; id < n; id++)
    {
      int start = id;
      while (p[start] != -1 && !visited[start])
      {
        start = p[start];
      }

      if (!visited[start])
      {
        mx = std::max(mx, dfs(dfs, start));
      }
    }

    return mx;
  }
};
