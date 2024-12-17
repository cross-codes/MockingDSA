package neetcode.practice.Sliding_Window;

import java.util.NoSuchElementException;
import java.util.stream.IntStream;

class Solution {
  boolean isValidRange(int start, int end, String s, int k, int[] frequency) {
    int maxFrequency = IntStream.of(frequency).max().orElseThrow(() -> new NoSuchElementException());
    return end - start + 1 - maxFrequency <= k;
  }

  public int characterReplacement(String s, int k) {
    int n = s.length();
    int[] frequency = new int[26];

    int leftMostBound = 0, currentPosition = 0, maxLength = 0;
    while (currentPosition < n) {
      char currentCharacter = s.charAt(currentPosition);
      frequency[currentCharacter - 'A']++;
      if (!this.isValidRange(leftMostBound, currentPosition, s, k, frequency)) {
        maxLength = Math.max(maxLength, currentPosition - leftMostBound);
        while (!this.isValidRange(leftMostBound, currentPosition, s, k, frequency)) {
          frequency[s.charAt(leftMostBound) - 'A']--;
          leftMostBound++;
        }
      }
      currentPosition++;
    }

    return Math.max(maxLength, n - leftMostBound);
  }
}