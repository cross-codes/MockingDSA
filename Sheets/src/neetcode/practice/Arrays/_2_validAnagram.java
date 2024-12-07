package neetcode.practice.Arrays;

import java.util.Arrays;

class Solution {
  public boolean isAnagram(String s, String t) {
    int[] frequencyS = new int[26], frequencyT = new int[26];
    for (char c : s.toCharArray())
      frequencyS[c - 'a']++;

    for (char c : t.toCharArray()) {
      frequencyT[c - 'a']++;
    }

    return Arrays.equals(frequencyS, frequencyT);
  }
}