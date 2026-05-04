#include <random>
#include <unordered_set>

class RandomizedSet
{
private:
  std::random_device random_device_;
  std::mt19937_64 engine_;

  std::unordered_set<int> set_{};

public:
  RandomizedSet() : engine_(random_device_())
  {
  }

  bool insert(int val)
  {
    if (set_.contains(val))
      return false;

    set_.insert(val);
    return true;
  }

  bool remove(int val)
  {
    if (set_.contains(val))
    {
      set_.erase(val);
      return true;
    }

    return false;
  }

  int getRandom()
  {
    int n{static_cast<int>(set_.size())};
    std::uniform_int_distribution<int> distribution(0, n - 1);

    int fwd{distribution(engine_)};
    auto it = set_.begin();
    std::advance(it, fwd);

    return *it;
  }
};
