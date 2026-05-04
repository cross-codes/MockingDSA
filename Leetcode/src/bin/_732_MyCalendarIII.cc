#include <set>
#include <vector>

class MyCalendarThree
{
private:
  enum EventType
  {
    END,
    START
  };

  std::multiset<std::vector<int>> events{};

public:
  MyCalendarThree()
  {
  }

  int book(int startTime, int endTime)
  {
    events.insert({startTime, EventType::START});
    events.insert({endTime, EventType::END});

    int mx{1}, curr{};
    for (const auto &v : events)
    {
      int type = v[1];
      if (type == EventType::START)
        curr += 1;
      else
        curr -= 1;

      mx = std::max(mx, curr);
    }

    return mx;
  }
};
