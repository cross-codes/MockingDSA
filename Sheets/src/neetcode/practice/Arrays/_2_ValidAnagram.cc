#include <cstring>
#include <string>

class Solution {
public:
  bool isAnagram(std::string s, std::string t) {
    int freq[26];

    std::memset(freq, 0x00, sizeof(freq));

    for (const char &c : s)
      freq[c - 'a']++;

    for (const char &c : t)
      freq[c - 'a']--;

    for (int num : freq) {
      if (num != 0)
        return false;
    }

    return true;
  }
};
