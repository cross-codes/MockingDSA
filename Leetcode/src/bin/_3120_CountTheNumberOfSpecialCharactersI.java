import java.util.stream.IntStream;

class Solution {
  public int numberOfSpecialChars(String word) {
    boolean[] present = new boolean[26 + 26];
    for (char c : word.toCharArray())
      present[Character.isUpperCase(c) ? c - 'A' + 26 : c - 'a'] = true;

    return (int) IntStream.range(0, 26).filter(i -> present[i] && present[i + 26]).count();
  }
}
