package neetcode.practice.Sliding_Window;

import java.util.HashMap;

class Solution {
  public int lengthOfLongestSubstring(String s) {
    HashMap<Character, Integer> uniqueCharToInt = new HashMap<>();
    int leftMostBound = 0, currentPos = 0, n = s.length();
    int maxSize = 0;
    while (currentPos < n) {
      char currentChar = s.charAt(currentPos);
      if (uniqueCharToInt.containsKey(currentChar)) {
        maxSize = Math.max(maxSize, uniqueCharToInt.size());
        int matchingIndex = uniqueCharToInt.get(currentChar);
        for (int i = leftMostBound; i <= matchingIndex; i++)
          uniqueCharToInt.remove(s.charAt(i));
        leftMostBound = matchingIndex + 1;
        uniqueCharToInt.put(currentChar, currentPos);
      } else
        uniqueCharToInt.put(currentChar, currentPos);
      currentPos++;
    }

    return Math.max(uniqueCharToInt.size(), maxSize);
  }
}