package strings;

import primitives.Integer.IntVector;

public class StringHash {
  public IntVector powers, prefixHashes;
  public long A;
  public int B;
  private int m;

  public StringHash(String s, long A, int B) {
    this.m = s.length();

    this.powers = new IntVector(this.m + 1);
    for (int i = 0; i <= this.m; i++)
      this.powers.add(1);

    this.prefixHashes = new IntVector(this.m + 1);
    for (int i = 0; i <= this.m; i++)
      this.prefixHashes.add(1);

    this.A = A;
    this.B = B;

    for (int i = 1; i <= this.m; i++) {
      this.powers.set(i, (int) (this.powers.get(i - 1) * this.A % this.B));
      this.prefixHashes.set(i, (int) ((this.prefixHashes.get(i - 1) * this.A + (long) (s.charAt(i - 1))) % this.B));
    }
  }

  public int getHash(int l, int r) {
    long h = (long) this.prefixHashes.get(r) - this.prefixHashes.get(l) * this.powers.get(r - l);
    return (int) ((h % this.B + this.B) % this.B);
  }
}
