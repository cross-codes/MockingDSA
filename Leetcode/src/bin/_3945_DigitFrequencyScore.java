class Solution {
  public int digitFrequencyScore(int n) {
    int[] freq = new int[10];
    while (n != 0) {
      freq[n % 10] += 1;
      n /= 10;
    }
    int res = 0;
    for (int d = 0; d < 10; d++)
      res += d * freq[d];

    return res;
  }
}
