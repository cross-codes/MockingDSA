#include <cmath>
#include <random>

struct Random {

  /*
   * Author: github.com/cross-codes
   */

private:
  std::random_device randomDevice_;
  std::mt19937_64 engine_;

  Random() : engine_(randomDevice_()) {};
  Random(const Random &) = delete;
  Random &operator=(const Random &) = delete;

public:
  static Random &getInstance() {
    static Random instance;
    return instance;
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextUniformRandomInteger(T p, T r) {
    std::uniform_int_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextUniformRandomReal(T p, T r) {
    std::uniform_real_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextNormalReal(T p, T r) {
    std::normal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  inline bool nextBernoulli() {
    std::bernoulli_distribution distribution;
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextBinomialReal(T p, T r) {
    std::binomial_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextPoissonReal(T p, T r) {
    std::poisson_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextExponentialReal(T p, T r) {
    std::exponential_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextGammaReal(T p, T r) {
    std::gamma_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextWeibullReal(T p, T r) {
    std::weibull_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextLogNormalReal(T p, T r) {
    std::lognormal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextChiSquaredReal(T p, T r) {
    std::chi_squared_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextCauchyReal(T p, T r) {
    std::cauchy_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T nextTDistributionReal(T p, T r) {
    std::student_t_distribution<T> distribution(p, r);
    return distribution(engine_);
  }
};
