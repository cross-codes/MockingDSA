namespace _2078;

public class Solution {
    public int MaxDistance(int[] colors) {
        int n = colors.Length, mx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (colors[i] != colors[j]) {
                    mx = Math.Max(mx, j - i);
                }
            }
        }

        return mx;
    }
}
