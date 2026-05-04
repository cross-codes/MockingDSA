class Solution {
    public boolean validDigit(int n, int x) {
        String equiv = String.valueOf(n);
        char c = Character.forDigit(x, 10);
        return equiv.indexOf(c) != -1 && equiv.charAt(0) != c;
    }
}
