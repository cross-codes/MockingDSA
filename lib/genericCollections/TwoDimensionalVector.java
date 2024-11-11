package genericCollections;

public class TwoDimensionalVector {
  private final int x;
  private final int y;

  public TwoDimensionalVector(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public long cross(TwoDimensionalVector vector) {
    return (long) this.x * vector.y - (long) this.y * vector.x;
  }

  public long dot(TwoDimensionalVector vector) {
    return (long) this.x * vector.x + (long) this.y * vector.y;
  }

  public double norm() {
    return Math.sqrt(this.x * this.x + this.y * this.y);
  }

  public TwoDimensionalVector add(TwoDimensionalVector vector) {
    return new TwoDimensionalVector(this.x + vector.x, this.y + vector.y);
  }

  public TwoDimensionalVector subtract(TwoDimensionalVector vector) {
    return new TwoDimensionalVector(this.x - vector.x, this.y - vector.y);
  }

  public TwoDimensionalVector perpendicularVector() {
    return new TwoDimensionalVector(-this.y, this.x);
  }

  public double angleBetween(TwoDimensionalVector vector) {
    double dotProduct = this.dot(vector);
    double normProduct = this.norm() * vector.norm();
    if (normProduct == 0)
      return (dotProduct < 0D) ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
    return Math.acos(dotProduct / normProduct);
  }

  public double angle() {
    if (this.x == 0)
      return this.y > 0 ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    return Math.atan2(this.y, this.x);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null || !(obj instanceof TwoDimensionalVector))
      return false;

    TwoDimensionalVector vector = (TwoDimensionalVector) obj;
    return this.x == vector.x && this.y == vector.y;
  }

  @Override
  public String toString() {
    return "<" + this.x + ", " + this.y + ">";
  }
}