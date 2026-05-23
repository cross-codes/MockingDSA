#include <algorithm>
#include <queue>
#include <vector>

class Solution
{
public:
  int mostBooked(int n, std::vector<std::vector<int>> &meetings)
  {
    std::vector<int> meetingCount(n, 0);
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>>
        usedRooms;
    std::priority_queue<int, std::vector<int>, std::greater<int>> unusedRooms;

    for (int i = 0; i < n; i++)
    {
      unusedRooms.push(i);
    }
    sort(meetings.begin(), meetings.end());

    for (auto meeting : meetings)
    {
      int start = meeting[0], end = meeting[1];

      while (!usedRooms.empty() && usedRooms.top().first <= start)
      {
        int room = usedRooms.top().second;
        usedRooms.pop();
        unusedRooms.push(room);
      }
      if (!unusedRooms.empty())
      {
        int room = unusedRooms.top();
        unusedRooms.pop();
        usedRooms.push({end, room});
        meetingCount[room]++;
      }
      else
      {
        auto [roomAvailabilityTime, room] = usedRooms.top();
        usedRooms.pop();
        usedRooms.push({roomAvailabilityTime + end - start, room});
        meetingCount[room]++;
      }
    }

    int maxMeetingCount = 0, maxMeetingCountRoom = 0;
    for (int i = 0; i < n; i++)
    {
      if (meetingCount[i] > maxMeetingCount)
      {
        maxMeetingCount     = meetingCount[i];
        maxMeetingCountRoom = i;
      }
    }
    return maxMeetingCountRoom;
  }
};
