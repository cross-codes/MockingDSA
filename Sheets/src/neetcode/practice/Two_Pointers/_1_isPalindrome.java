package neetcode.practice.Two_Pointers;

class Solution {
  public boolean isPalindrome(String s) {
    char[] representation = s.replaceAll("[^a-zA-Z0-9]", "").toCharArray();
    int l = 0, r = representation.length - 1;
    while (l < r) {
      char left = Character.toLowerCase(representation[l++]);
      char right = Character.toLowerCase(representation[r--]);

      if (left != right)
        return false;
    }
    return true;
  }
}