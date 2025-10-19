#include <random>
#include <string>
#include <vector>

class Solution
{

  struct StringHash
  {
  private:
    int n;

  public:
    std::vector<int> powers{}, prefix_hashes{};
    int64_t A;
    int B;

    StringHash(const std::string &s, int64_t _A, int _B)
        : n(static_cast<int>(s.length())), powers(n + 1, 1),
          prefix_hashes(n + 1, 0), A{_A}, B{_B}
    {
      for (int i = 1; i <= n; i++)
      {
        powers[i] = powers[i - 1] * A % B;
        prefix_hashes[i] =
            (prefix_hashes[i - 1] * A + static_cast<int64_t>(s[i - 1])) % B;
      }
    }

    int get_hash(int l, int r)
    {
      int64_t h = static_cast<int64_t>(prefix_hashes[r]) -
                  static_cast<int64_t>(prefix_hashes[l]) * powers[r - l];
      return (h % B + B) % B;
    }
  };

public:
  std::vector<int> longestCommonPrefix(std::vector<std::string> &words)
  {
    int n = static_cast<int>(words.size());

    std::mt19937_64 rng;
    std::random_device rd;
    rng.seed(rd());

    int B     = static_cast<int>(1e9 - 7);
    int64_t A = std::uniform_int_distribution<int64_t>(
        B / 10, 9 * static_cast<int64_t>(B) / 10)(rng);

    std::vector<StringHash> hashes{};
    for (const std::string &word : words)
      hashes.emplace_back(word, A, B);

    auto pred = [](StringHash &a, StringHash &b, int l) -> bool {
      return a.get_hash(0, l + 1) == b.get_hash(0, l + 1);
    };

    auto lcp = [&words, &pred](StringHash &a, StringHash &b, int idx1,
                               int idx2) -> int {
      int a_sz = static_cast<int>(words[idx1].size());
      int b_sz = static_cast<int>(words[idx2].size());

      int L{-1}, R{std::min(a_sz, b_sz)};
      while (R - L > 1)
      {
        int M                    = std::midpoint(L, R);
        (!pred(a, b, M) ? R : L) = M;
      }

      return R;
    };

    int mx{-1}, smx{}, mx_idx{-1};

    for (int i = 0; i < n - 1; i++)
    {
      int length = lcp(hashes[i], hashes[i + 1], i, i + 1);
      if (length > mx)
      {
        smx    = mx;
        mx_idx = i;
        mx     = length;
      }
      else if (length > smx)
        smx = length;
    }

    std::vector<int> res{};
    for (int i = 0; i < n; i++)
    {
      int nl{};
      if (i != 0 && i != n - 1)
        nl = lcp(hashes[i - 1], hashes[i + 1], i - 1, i + 1);

      if (i != mx_idx && i != mx_idx + 1)
        res.push_back(std::max(mx, nl));
      else
        res.push_back(std::max(nl, smx));
    }

    return res;
  }
};
