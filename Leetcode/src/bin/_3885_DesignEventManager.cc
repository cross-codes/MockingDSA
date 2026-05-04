#include <set>
#include <unordered_map>
#include <vector>

class EventManager
{
public:
  EventManager(std::vector<std::vector<int>> &events)
  {
    int n = static_cast<int>(events.size());
    for (int i = 0; i < n; i++)
    {
      m_events.insert({events[i][1], -events[i][0]});
      m_event_to_priority[events[i][0]] = events[i][1];
    }
  }

  void updatePriority(int eventId, int newPriority)
  {
    int old_priority = m_event_to_priority[eventId];
    auto it          = m_events.lower_bound({old_priority, -eventId});
    m_events.erase(it);
    m_events.insert({newPriority, -eventId});
    m_event_to_priority[eventId] = newPriority;
  }

  int pollHighest()
  {
    if (m_events.empty())
    {
      return -1;
    }
    auto last = std::prev(m_events.end());
    int e     = last->second;
    m_events.erase(std::prev(m_events.end()));
    return -e;
  }

private:
  std::multiset<std::pair<int, int>> m_events{};
  std::unordered_map<int, int> m_event_to_priority{};
};
