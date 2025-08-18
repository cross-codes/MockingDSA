#include "runner.hh"

namespace Day7
{

auto pt1() -> void
{
  int64_t tot{};
  for (std::string s; std::getline(std::cin, s);)
  {
    std::string target{};
    const char delim = ':';

    std::istringstream line(s);
    std::getline(line, target, delim);

    int64_t val = std::stoll(target);
    std::vector<int> operands{};
    for (int x; line >> x;)
      operands.push_back(x);

    int N = static_cast<int>(operands.size()) - 1, signs[N];
    for (int i = 0; i < (1 << N); i++)
    {
      std::memset(signs, 0x00, sizeof signs);
      for (int j = 0; j < N; j++)
        if (i & (1 << j))
          signs[j] = 1;

      int64_t eval{operands.front()};
      for (int j = 1; j < N + 1; j++)
        if (signs[j - 1] == 1)
          eval *= operands[j];
        else
          eval += operands[j];

      if (eval == val)
      {
        tot += val;
        break;
      }
    }
  }
  std::cout << tot << "\n";
}

auto pt2() -> void
{
  auto half_pow = [](auto &&half_pow, int x, int n) -> int64_t {
    if (n == 0)
      return 1;

    int64_t u = half_pow(half_pow, x, n >> 1);
    u         = u * u;

    if (n & 1)
      u = u * x;

    return u;
  };

  auto conv_rev = [](int num, int base) -> std::string {
    const std::string chars = "0123456789";

    std::string res{};
    while (num != 0)
    {
      res.push_back(chars[num % base]);
      num /= base;
    }

    return res;
  };

  int64_t tot{};
  for (std::string s; std::getline(std::cin, s);)
  {
    std::string target{};
    const char delim = ':';

    std::istringstream line(s);
    std::getline(line, target, delim);

    int64_t val = std::stoll(target);
    std::vector<int> operands{};
    for (int x; line >> x;)
      operands.push_back(x);

    int N              = static_cast<int>(operands.size()) - 1, signs[N];
    const int64_t ulim = half_pow(half_pow, 3, N);

    for (int i = 0; i < ulim; i++)
    {
      std::memset(signs, 0x00, sizeof signs);
      std::string repr = conv_rev(i, 3);

      while (static_cast<int>(repr.length()) < N)
        repr += '0';

      int sz = static_cast<int>(repr.size());

      for (int j = 0; j < sz; j++)
        if (repr[j] == '1')
          signs[j] = 1;
        else if (repr[j] == '2')
          signs[j] = 2;

      int64_t eval{operands.front()};
      for (int j = 1; j < N + 1; j++)
        if (signs[j - 1] == 1)
          eval *= operands[j];
        else if (signs[j - 1] == 2)
        {
          std::string temp = std::to_string(eval);
          temp += std::to_string(operands[j]);
          eval = std::stoll(temp);
        }
        else
          eval += operands[j];

      if (eval == val)
      {
        tot += val;
        break;
      }
    }
  }

  std::cout << tot << "\n";
}

} // namespace Day7

int main()
{
  Runner::init();
  Runner::exec_all(Day7::pt1, Day7::pt2);
  Runner::end();
  return 0;
}
