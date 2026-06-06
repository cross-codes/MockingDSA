#include <cmath>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  std::vector<int> numberOfPairs(std::vector<int> &a, std::vector<int> &nums2,
                                 std::vector<std::vector<int>> &queries)
  {
    int n          = static_cast<int>(nums2.size());
    int bsz        = static_cast<int>(std::sqrt(n));
    int num_blocks = (n + bsz - 1) / bsz;

    std::vector<int64_t> elements(n);
    for (int i = 0; i < n; i++)
      elements[i] = nums2[i];

    std::vector<std::unordered_map<int64_t, int>> block_maps(num_blocks);
    std::vector<int64_t> lazy(num_blocks, 0);

    for (int i = 0; i < n; i++)
    {
      int curb = i / bsz;
      block_maps[curb][elements[i]]++;
    }

    auto updater = [&](int b, int idx, int64_t val) {
      int64_t old_val = elements[idx];
      block_maps[b][old_val]--;
      if (block_maps[b][old_val] == 0)
      {
        block_maps[b].erase(old_val);
      }
      elements[idx] += val;
      block_maps[b][elements[idx]]++;
    };

    std::vector<int> answers;
    for (const auto &query : queries)
    {
      if (query[0] == 1)
      {
        int x = query[1], y = query[2];
        int64_t val = query[3];

        int startb = x / bsz, endb = y / bsz;

        if (startb == endb)
        {
          for (int i = x; i <= y; i++)
            updater(startb, i, val);
        }
        else
        {
          int end_of_sb = (startb + 1) * bsz - 1;
          for (int i = x; i <= end_of_sb; i++)
          {
            updater(startb, i, val);
          }

          for (int b = startb + 1; b < endb; b++)
          {
            lazy[b] += val;
          }

          int start_of_eb = endb * bsz;
          for (int i = start_of_eb; i <= y; i++)
          {
            updater(endb, i, val);
          }
        }
      }
      else
      {
        int tot = query[1];
        int cnt = 0;

        for (int e : a)
        {
          int64_t target = static_cast<int64_t>(tot) - e;
          for (int b = 0; b < num_blocks; b++)
          {
            int64_t tgt = target - lazy[b];
            auto it     = block_maps[b].find(tgt);
            if (it != block_maps[b].end())
            {
              cnt += it->second;
            }
          }
        }
        answers.push_back(cnt);
      }
    }

    return answers;
  }
};
