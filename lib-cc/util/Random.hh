#include <random>

struct Random {
 public:
  static Random& get_instance() {
    static Random instance;
    return instance;
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_uniform_int(T p, T r) {
    std::uniform_int_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_uniform_real(T p, T r) {
    std::uniform_real_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_normal_real(T p, T r) {
    std::normal_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  inline bool next_bernoulli() {
    std::bernoulli_distribution distribution;
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_binomial_real(T p, T r) {
    std::binomial_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_poisson_real(T p, T r) {
    std::poisson_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_exponential_real(T p, T r) {
    std::exponential_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_gamma_real(T p, T r) {
    std::gamma_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_weibull_real(T p, T r) {
    std::weibull_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_log_normal_real(T p, T r) {
    std::lognormal_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_chi_squared_real(T p, T r) {
    std::chi_squared_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_cauchy_real(T p, T r) {
    std::cauchy_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_t_distribution_real(T p, T r) {
    std::student_t_distribution<T> distribution(p, r);
    return distribution(m_engine);
  }

 private:
  std::random_device m_random_device;
  std::mt19937_64 m_engine;

  Random() : m_engine(m_random_device()) {}
  Random(const Random&)            = delete;
  Random& operator=(const Random&) = delete;
};
