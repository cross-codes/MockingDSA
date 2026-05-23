class Solution {
    public int countKthRoots(int l, int r, int k) {
        int mn = (int) Math.ceil(Math.round(Math.pow(l, 1.0 / k) * 1e9) / 1e9);
        int mx = (int) Math.floor(Math.round(Math.pow(r, 1.0 / k) * 1e9) / 1e9);
        if (Math.pow(mn, k) < l) mn++;
        if (Math.pow(mx, k) > r) mx--;

        return (mx >= mn) ? (mx - mn + 1) : 0;
    }
}
