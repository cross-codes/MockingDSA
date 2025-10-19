#include <string>
#include <vector>

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
