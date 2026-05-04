#include <cstring>
#include <memory>
#include <string>

struct Anagram {
private:
  std::unique_ptr<int[]> freq_;

public:
  Anagram(std::string s) : freq_(new int[26]) {
    std::memset(freq_.get(), 0x00, sizeof(int) * 26);
    for (const char &c : s)
      freq_[c - 'a']++;
  }

  bool operator==(const std::unique_ptr<int[]> &a) const {
    for (std::size_t i = 0; i < 26; i++) {
      if (a[i] != freq_[i])
        return false;
    }

    return true;
  }
};

class Solution {
public:
  bool checkInclusion(std::string s1, std::string s2) {
    auto reduce = Anagram(s1);
    std::size_t n = s2.size();

    std::unique_ptr<int[]> freq(new int[26]);
    std::memset(freq.get(), 0x00, sizeof(int) * 26);

    std::ptrdiff_t l = 0;
    for (std::size_t i = 0; i < s1.size(); i++)
      freq[s2[i] - 'a']++;

    if (reduce == freq)
      return true;

    for (std::size_t i = s1.size(); i < n; i++) {
      freq[s2[l] - 'a']--;
      freq[s2[i] - 'a']++;

      l++;
      if (reduce == freq)
        return true;
    }

    return false;
  }
};
