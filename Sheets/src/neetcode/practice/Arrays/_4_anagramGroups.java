package neetcode.practice.Arrays;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

class Solution {
  public List<List<String>> groupAnagrams(String[] strs) {
    List<List<String>> res = new ArrayList<>();
    HashMap<Anagram, Integer> locations = new HashMap<>();

    for (String s : strs) {
      Anagram equiv = new Anagram(s);
      int index = locations.computeIfAbsent(equiv, k -> {
        res.add(new ArrayList<>());
        return res.size() - 1;
      });
      res.get(index).add(equiv.underlyingString);
    }

    return res;
  }
}

class Anagram {
  public int[] freq = new int[26];
  private int length;
  public String underlyingString;

  public Anagram(String s) {
    this.underlyingString = s;
    this.length = s.length();

    for (int i = 0; i < this.length; i++) {
      char c = s.charAt(i);
      this.freq[c - 'a']++;
    }
  }

  @Override
  public boolean equals(Object o) {
    if (!(o instanceof Anagram))
      return false;
    Anagram obj = (Anagram) o;
    if (!Arrays.equals(obj.freq, this.freq))
      return false;
    return true;
  }

  @Override
  public int hashCode() {
    int res = 1;
    for (int i = 0; i < 26; i++)
      res = 31 * res + this.freq[i];
    return res;
  }
}