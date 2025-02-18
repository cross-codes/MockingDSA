#include <string>

class Solution {
public:
  bool isMatch(std::string s, std::string p) {
    std::size_t sSize = s.size(), pSize = p.size();
    std::size_t patternPos = 0, stringPos = 0;

    char prev = '.';
    while (stringPos != sSize && patternPos != pSize) {
      char sChar = s[stringPos], pChar = p[stringPos];
      if (pChar == '.') {
        stringPos++, patternPos++;
      } else if (pChar == '*') {
        if (prev == '.') {
          stringPos++;
        } else {
          if (sChar != prev) {
            prev = sChar;
            patternPos++;
          } else
            stringPos++;
        }
      } else {
        if (pChar != sChar &&
            (patternPos != pSize - 1 && p[patternPos + 1] != '*'))
          return false;
        prev = sChar;
        stringPos++, patternPos++;
      }
    }

    if (stringPos == sSize && (patternPos == pSize || p[pSize - 1] == '*'))
      return true;
    else
      return false;
  }
};
