#include "include/runner.hh"

namespace Day5
{

auto pt1() -> void
{
  std::unordered_map<int, std::unordered_set<int>> is_behind{};

  for (std::string s; std::getline(std::cin, s);)
  {
    if (s == "")
      break;

    auto pos = s.find('|');
    is_behind[std::stoi(s.substr(0, pos))].insert(
        std::stoi(s.substr(pos + 1, std::string::npos)));
  }

  auto PARTIAL_ORDERING = [&is_behind](const int &a, const int &b) -> bool {
    return is_behind[a].contains(b);
  };

  const char delim = ',';

  int gcnt{};
  for (std::string s; std::getline(std::cin, s);)
  {
    std::istringstream iss(s);
    std::vector<int> res{};

    int x;
    std::string temp{};
    while (std::getline(iss, temp, delim))
      if (std::istringstream(temp) >> x)
        res.push_back(x);

    if (std::is_sorted(res.begin(), res.end(), PARTIAL_ORDERING))
      gcnt += res[res.size() >> 1];
  }

  std::cout << gcnt << "\n";
}

auto pt2() -> void
{
  std::unordered_map<int, std::unordered_set<int>> is_behind{};

  for (std::string s; std::getline(std::cin, s);)
  {
    if (s == "")
      break;

    auto pos = s.find('|');
    is_behind[std::stoi(s.substr(0, pos))].insert(
        std::stoi(s.substr(pos + 1, std::string::npos)));
  }

  auto PARTIAL_ORDERING = [&is_behind](const int &a, const int &b) -> bool {
    return is_behind[a].contains(b);
  };

  const char delim = ',';

  int gcnt{};
  for (std::string s; std::getline(std::cin, s);)
  {
    std::istringstream iss(s);
    std::vector<int> res{};

    int x;
    std::string temp{};
    while (std::getline(iss, temp, delim))
      if (std::istringstream(temp) >> x)
        res.push_back(x);

    if (!std::is_sorted(res.begin(), res.end(), PARTIAL_ORDERING))
    {
      std::sort(res.begin(), res.end(), PARTIAL_ORDERING);
      gcnt += res[res.size() >> 1];
    }
  }

  std::cout << gcnt << "\n";
}

} // namespace Day5

int main()
{
  Runner::init();
  Runner::exec_all(Day5::pt1, Day5::pt2);
  Runner::end();
  return 0;
}
