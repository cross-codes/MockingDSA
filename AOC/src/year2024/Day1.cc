#include "include/runner.hh"

namespace Day1
{

auto pt1() -> void
{
  std::vector<int64_t> l1{}, l2{};
  int64_t x, y;
  while (std::cin >> x >> y)
  {
    l1.push_back(x);
    l2.push_back(y);
  }

  std::sort(l1.begin(), l1.end());
  std::sort(l2.begin(), l2.end());

  std::valarray<int64_t> gv1(l1.data(), l1.size()), gv2(l2.data(), l2.size());

  std::cout << std::abs(gv1 - gv2).sum() << "\n";
}

auto pt2() -> void
{
  std::vector<int64_t> l1{};
  std::unordered_map<int64_t, int> cnt2{};
  int64_t x, y;
  while (std::cin >> x >> y)
  {
    l1.push_back(x);
    cnt2[y] += 1;
  }

  int64_t score{};
  for (int64_t e : l1)
    score += e * cnt2[e];

  std::cout << score << "\n";
}

} // namespace Day1

int main()
{
  Runner::init();
  Runner::exec_all(Day1::pt1, Day1::pt2);
  Runner::end();
  return 0;
}
