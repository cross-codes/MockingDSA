#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct Anagram {
public:
  std::unique_ptr<int[]> freq;
  std::string underlyingString;

  Anagram(std::string s)
      : freq(std::make_unique<int[]>(26)), underlyingString(s) {
    std::memset(freq.get(), 0x00, sizeof(int) * 26);
    for (char c : s)
      freq[c - 'a']++;
  }

  bool operator==(const Anagram &o) const {
    for (size_t i = 0; i < 26; i++)
      if (freq[i] != o.freq[i])
        return false;

    return true;
  }

  struct AnagramHash {
    size_t operator()(const Anagram &a) const {
      size_t hash = 1;
      for (size_t i = 0; i < 26; i++)
        hash = 31 * hash + a.freq[i];

      return hash;
    }
  };
};

class Solution {
public:
  std::vector<std::vector<std::string>>
  groupAnagrams(std::vector<std::string> &strs) {

    std::vector<std::vector<std::string>> res;
    std::unordered_map<Anagram, size_t, Anagram::AnagramHash> typeToIndex{};

    for (auto &string : strs) {
      Anagram equiv(string);
      auto it = typeToIndex.find(equiv);

      if (it != typeToIndex.end())
        res[it->second].push_back(string);
      else {
        typeToIndex[equiv] = res.size();
        res.push_back({string});
      }
    }

    return res;
  }
};
