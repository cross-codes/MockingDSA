#include <string>
#include <unordered_map>
#include <set>

class TimeMap
{
private:
  std::unordered_map<std::string, std::set<std::pair<int, std::string>>>
      timeMap_;

public:
  TimeMap() : timeMap_{}
  {
  }

  void set(std::string key, std::string value, int timeStamp)
  {
    timeMap_[key].emplace(timeStamp, value);
  }

  std::string get(std::string key, int timeStamp)
  {
    const auto &set = timeMap_[key];
    auto it         = set.lower_bound({timeStamp, ""});
    if (it == set.begin())
      return (it->first == timeStamp) ? it->second : "";
    else
      return (it->first == timeStamp) ? it->second : (--it)->second;
  }
};
