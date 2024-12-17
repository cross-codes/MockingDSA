package neetcode.practice.Sliding_Window;

import java.util.Arrays;

class Solution {
  public boolean checkInclusion(String s1, String s2) {
    int length1 = s1.length(), length2 = s2.length();
    if (length2 < length1)
      return false;

    int left = 0, right = left + length1;
    Anagram target = new Anagram(s1);
    while (right <= length2) {
      Anagram current = new Anagram(s2.substring(left, right));
      if (current.equals(target))
        return true;

      left++;
      right++;
    }

    return false;
  }
}

class Anagram {
  public String underlyingString;
  private int[] freq = new int[26];
  private int length;

  public Anagram(String s) {
    this.underlyingString = s;
    this.length = s.length();
    for (int i = 0; i < this.length; i++)
      this.freq[s.charAt(i) - 'a']++;
  }

  @Override
  public boolean equals(Object o) {
    if (!(o instanceof Anagram))
      return false;
    if (o instanceof int[])
      return Arrays.equals(this.freq, (int []) o);

    Anagram equiv = (Anagram) o;
    return Arrays.equals(this.freq, equiv.freq);
  }
}