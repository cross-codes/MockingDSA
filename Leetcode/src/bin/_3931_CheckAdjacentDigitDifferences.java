package bin;

class Solution {
  public boolean isAdjacentDiffAtMostTwo(String s) {
    int n = s.length();
    boolean ok = true;
    for (int i = 0; i < n - 1; i++) {
      int left = Character.getNumericValue(s.charAt(i));
      int right = Character.getNumericValue(s.charAt(i + 1));
      ok &= Math.abs(right - left) <= 2;
    }

    return ok;
  }
}
