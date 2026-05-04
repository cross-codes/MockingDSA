#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>

namespace _10428
{
auto f(int N, double coeff[], double x) -> double
{
  double val{};
  for (int i = 0; i <= N; i++)
    val += std::pow(x, i) * coeff[i];

  return val;
}

auto f_prime(int N, double coeff[], double mult_der[], double x) -> double
{
  double val{};
  for (int i = 1; i <= N; i++)
    val += std::pow(x, i - 1) * coeff[i] * mult_der[i];

  return val;
}

auto root_newton(int N, double coeff[], double mult_der[], double guess)
    -> double
{
  double epsilon{1e-6}, x{guess};

  while (true)
  {
    double nx = x - f(N, coeff, x) / f_prime(N, coeff, mult_der, x);
    if (std::abs(x - nx) < epsilon)
      break;

    x = nx;
  }

  return std::round(x * 10000.0) / 10000.0;
}

auto run(int _case, int N) -> void
{
  double coeff[N + 1], mult[N + 1];
  for (int i = 0; i < N + 1; i++)
    std::cin >> coeff[i];

  std::iota(mult, mult + N + 1, 0);
  std::reverse(coeff, coeff + N + 1);

  std::set<double> roots{};
  for (double x = -25; x <= 25; x += 0.2)
  {
    double root = root_newton(N, coeff, mult, x);
    if (roots.find(root) == roots.end())
      roots.insert(root);
  }

  std::cout << "Equation " << _case << ": ";
  for (const double &root : roots)
    std::cout << std::fixed << std::setprecision(4) << root << " ";

  std::cout << "\n";
}
} // namespace _10428

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{1}, N{};
  while (std::cin >> N)
    _10428::run(t++, N);
}
