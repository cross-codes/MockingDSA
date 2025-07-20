#include <string>

class Solution
{
public:
  bool isValid(std::string word)
  {
    std::string v = "aeiouAEIOU";
    int vowel{}, consonant{};
    for (char c : word)
    {
      if (v.contains(c))
        vowel += 1;
      else if (std::isalpha(c))
        consonant += 1;
      else if (!std::isdigit(c))
        return false;
    }

    return word.length() >= 3 && vowel >= 1 && consonant >= 1;
  }
};
