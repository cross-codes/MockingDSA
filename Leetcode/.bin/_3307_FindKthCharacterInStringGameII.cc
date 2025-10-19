#include <cstdint>
#include <vector>

class Solution
{
public:
  char kthCharacter(int64_t k, std::vector<int> &operations)
  {
    auto gpow2 = [](uint64_t k) -> int64_t {
      k -= 1;
      return std::bit_floor(k);
    };

    auto total_acc = [&gpow2, &operations](auto &&total_acc,
                                           uint64_t k) -> int64_t {
      if (k == 1)
        return 0;

      int64_t offset  = gpow2(k);
      int64_t new_pos = k - offset;

      return operations[std::__lg(offset)] + total_acc(total_acc, new_pos);
    };

    int64_t res = total_acc(total_acc, k);
    res %= 26;

    return static_cast<char>('a' + res);
  }
};

int main()
{
  std::vector<int> op = {0, 1, 0, 1};
  Solution().kthCharacter(15, op);
}
