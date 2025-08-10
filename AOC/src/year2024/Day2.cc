#include "include/runner.hh"

namespace Day2
{

auto pt1() -> void
{
  auto INCREASING = [](const int &a, const int &b) -> bool { return a < b; };
  auto DECREASING = [](const int &a, const int &b) -> bool { return a > b; };

  int cnt{};
  for (std::string line; std::getline(std::cin, line);)
  {
    std::istringstream iss(line);
    std::vector<int> split{};
    int x;
    while (iss >> x)
      split.push_back(x);

    int n = static_cast<int>(split.size());

    if (std::is_sorted(split.begin(), split.end(), INCREASING))
    {
      for (int i = 1; i < n; i++)
        if (split[i] - split[i - 1] > 3 || split[i] == split[i - 1])
          goto nxt;

      cnt += 1;
    }
    else if (std::is_sorted(split.begin(), split.end(), DECREASING))
    {
      for (int i = 1; i < n; i++)
        if (split[i - 1] - split[i] > 3 || split[i - 1] == split[i])
          goto nxt;

      cnt += 1;
    }
  nxt:
  }

  std::cout << cnt << "\n";
}

auto pt2() -> void
{
  auto INCREASING = [](const int &a, const int &b) -> bool { return a < b; };
  auto DECREASING = [](const int &a, const int &b) -> bool { return a > b; };

  int cnt{};
  for (std::string line; std::getline(std::cin, line);)
  {
    std::istringstream iss(line);
    std::vector<int> split{};
    int x;
    while (iss >> x)
      split.push_back(x);

    int n = static_cast<int>(split.size());

    bool found{};
    if (std::is_sorted(split.begin(), split.end(), INCREASING))
    {
      bool ok{true};
      for (int i = 1; i < n; i++)
        if (split[i] - split[i - 1] > 3 || split[i] == split[i - 1])
        {

          ok = false;
          break;
        }

      if (ok)
      {
        cnt += 1;
        found = true;
      }
    }
    else if (std::is_sorted(split.begin(), split.end(), DECREASING))
    {
      bool ok{true};
      for (int i = 1; i < n; i++)
        if (split[i - 1] - split[i] > 3 || split[i - 1] == split[i])
        {
          ok = false;
          break;
        }

      if (ok)
      {
        cnt += 1;
        found = true;
      }
    }

    if (found)
      continue;

    std::vector<std::vector<int>> cont{};
    for (int i = 0; i < n; i++)
    {
      std::vector<int> cand{};
      for (int j = 0; j < n; j++)
        if (j == i)
          continue;
        else
          cand.push_back(split[j]);

      cont.push_back(cand);
    }

    for (const auto &v : cont)
    {
      if (std::is_sorted(v.begin(), v.end(), INCREASING))
      {
        bool ok{true};
        for (int i = 1; i < n - 1; i++)
          if (v[i] - v[i - 1] > 3 || v[i] == v[i - 1])
          {
            ok = false;
            break;
          }

        if (ok)
        {
          cnt += 1;
          found = true;
        }
      }
      else if (std::is_sorted(v.begin(), v.end(), DECREASING))
      {
        bool ok{true};
        for (int i = 1; i < n - 1; i++)
          if (v[i - 1] - v[i] > 3 || v[i - 1] == v[i])
          {
            ok = false;
            break;
          }

        if (ok)
        {
          cnt += 1;
          found = true;
        }
      }

      if (found)
        break;
    }
  }

  std::cout << cnt << "\n";
}

} // namespace Day2

int main()
{
  Runner::init();
  Runner::exec_all(Day2::pt1, Day2::pt2);
  Runner::end();
  return 0;
}
