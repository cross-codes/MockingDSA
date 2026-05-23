#include <random>
#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
private:
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
  std::vector<std::string> partitionString(std::string s)
  {
    int n = static_cast<int>(s.size());

    std::mt19937_64 rng;
    std::random_device rd;
    rng.seed(rd());

    int B     = static_cast<int>(1e9 - 7);
    int64_t A = std::uniform_int_distribution<int64_t>(
        B / 10, 9 * static_cast<int64_t>(B) / 10)(rng);

    StringHash h(s, A, B);

    std::unordered_set<int> seen{};
    std::vector<std::string> res{};

    int l{}, r{};
    while (r < n)
    {
      int hash = h.get_hash(l, r + 1);
      if (!seen.contains(hash))
      {
        res.push_back(s.substr(l, r - l + 1));
        seen.insert(hash);
        l = r + 1;
      }

      r += 1;
    }

    return res;
  }
};
