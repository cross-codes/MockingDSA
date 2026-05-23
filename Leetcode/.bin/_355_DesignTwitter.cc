#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct DescendingTime
{
  bool operator()(const std::tuple<int, int, int> &a,
                  const std::tuple<int, int, int> &b) const noexcept
  {
    return std::get<0>(a) > std::get<0>(b);
  }
};

class Twitter
{
private:
  std::array<std::unordered_set<int>, 100> followed_by_{};

  std::unordered_map<int, std::vector<std::pair<int, int>>>
      tweets_{}; // userId: time_, tweetId

  std::array<std::multiset<std::tuple<int, int, int>, DescendingTime>, 100>
      feeds_{}; // time_, userId, tweetId

  int time_{};

public:
  Twitter()
  {
    time_ = 0;
    for (int i = 0; i < 100; i++)
      followed_by_[i].insert(i);
  }

  void postTweet(int userId, int tweetId)
  {
    time_ += 1;
    auto metadata = std::make_tuple(time_, userId, tweetId);
    for (const auto &followerId : followed_by_[userId])
      feeds_[followerId].insert(metadata);

    tweets_[userId].emplace_back(time_, tweetId);
  }

  std::vector<int> getNewsFeed(int userId)
  {
    std::vector<int> res{};
    int cnt{};
    for (auto it = feeds_[userId].begin();
         it != feeds_[userId].end() && cnt < 10; ++it, ++cnt)
    {
      auto tuple = *it;
      res.push_back(std::get<2>(tuple));
    }

    return res;
  }

  void follow(int followerId, int followeeId)
  {
    if (followerId == followeeId ||
        followed_by_[followeeId].contains(followerId))
      return;

    followed_by_[followeeId].insert(followerId);

    auto &feed = feeds_[followerId];
    for (const auto &pair : tweets_[followeeId])
    {
      auto metadata = std::make_tuple(pair.first, followeeId, pair.second);
      feed.insert(metadata);
    }
  }

  void unfollow(int followerId, int followeeId)
  {
    if (followerId == followeeId)
      return;

    followed_by_[followeeId].erase(followerId);

    auto &feed = feeds_[followerId];
    for (const auto &pair : tweets_[followeeId])
    {
      auto to_erase = std::make_tuple(pair.first, followeeId, pair.second);
      feed.erase(to_erase);
    }
  }
};
