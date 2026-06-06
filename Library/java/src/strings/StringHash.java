package strings;

import primitives.Integer.IntVector;

public class StringHash {
  public IntVector powers, prefixHashes, suffixHashes;
  public long A;
  public int B;
  public int m;

  public StringHash(String s, long A, int B) {
    this.m = s.length();

    this.powers = new IntVector(this.m + 1);
    this.prefixHashes = new IntVector(this.m + 1);
    this.suffixHashes = new IntVector(this.m + 1);

    for (int i = 0; i <= this.m; i++) {
      this.powers.add(1);
      this.prefixHashes.add(1);
      this.suffixHashes.add(1);
    }

    this.A = A;
    this.B = B;

    for (int i = 1; i <= this.m; i++) {
      long p = (this.powers.get(i - 1) * this.A) % this.B;
      this.powers.set(i, (int) ((p + this.B) % this.B));

      long ph = (this.prefixHashes.get(i - 1) * this.A + s.charAt(i - 1)) % this.B;
      this.prefixHashes.set(i, (int) ((ph + this.B) % this.B));

      long sh = (this.suffixHashes.get(i - 1) * this.A + s.charAt(this.m - i)) % this.B;
      this.suffixHashes.set(i, (int) ((sh + this.B) % this.B));
    }
  }

  public int getHash(int l, int r) {
    long h = (long) this.prefixHashes.get(r) - (long) this.prefixHashes.get(l) * this.powers.get(r - l);
    return (int) ((h % this.B + this.B) % this.B);
  }

  public int getReverseHash(int l, int r) {
    int revL = this.m - r;
    int revR = this.m - l;
    long h = (long) this.suffixHashes.get(revR) - (long) this.suffixHashes.get(revL) * this.powers.get(revR - revL);
    return (int) ((h % this.B + this.B) % this.B);
  }

  public long getBidirectionalHash(int l, int r) {
    long forward = getHash(l, r);
    long backward = getReverseHash(l, r);
    return (forward << 32) | (backward & 0xFFFFFFFFL);
  }
}
