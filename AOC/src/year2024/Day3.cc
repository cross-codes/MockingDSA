#include "include/runner.hh"

namespace Day3
{

auto pt1() -> void
{
  int64_t tot{};
  const std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)",
                           std::regex_constants::ECMAScript);

  for (std::string s; std::getline(std::cin, s);)
  {
    auto begin = std::sregex_iterator(s.begin(), s.end(), pattern);
    auto end   = std::sregex_iterator();

    for (auto i = begin; i != end; i++)
    {
      auto match = *i;
      int a      = std::stoi(match[1].str());
      int b      = std::stoi(match[2].str());
      tot += a * b;
    }
  }

  std::cout << tot << "\n";
}

auto pt2() -> void
{
  int64_t tot{};
  const std::regex pattern(
      "mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)",
      std::regex_constants::ECMAScript);

  bool stop{};
  for (std::string s; std::getline(std::cin, s);)
  {
    auto begin = std::sregex_iterator(s.begin(), s.end(), pattern);
    auto end   = std::sregex_iterator();

    for (auto i = begin; i != end; i++)
    {
      auto match = *i;
      if (match[0].str() == "do()")
        stop = false;
      else if (match[0].str() == "don't()")
        stop = true;
      else if (!stop)
      {
        int a = std::stoi(match[1].str());
        int b = std::stoi(match[2].str());
        tot += a * b;
      }
    }
  }

  std::cout << tot << "\n";
}

} // namespace Day3

int main()
{
  Runner::init();
  Runner::exec_all(Day3::pt1, Day3::pt2);
  Runner::end();
  return 0;
}
