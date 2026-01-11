package geometry;

public class Vector2D {

  public final int x;
  public final int y;

  public Vector2D(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public double norm() {
    return Math.sqrt(this.x * this.x + this.y * this.y);
  }

  public Vector2D add(Vector2D vector) {
    return new Vector2D(this.x + vector.x, this.y + vector.y);
  }

  public Vector2D subtract(Vector2D vector) {
    return new Vector2D(this.x - vector.x, this.y - vector.y);
  }

  public long dot(Vector2D vector) {
    return (long) this.x * vector.x + (long) this.y * vector.y;
  }

  public long cross(Vector2D vector) {
    return (long) this.x * vector.y - (long) this.y * vector.x;
  }

  public Vector2D perpendicularVector() {
    return new Vector2D(-this.y, this.x);
  }

  public double angle() {
    if (this.x == 0)
      return this.y > 0 ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    return Math.atan2(this.y, this.x);
  }

  public double angleBetween(Vector2D vector) {
    double dotProduct = this.dot(vector);
    double normProduct = this.norm() * vector.norm();
    if (normProduct == 0)
      return (dotProduct > 0D) ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    return Math.acos(dotProduct / normProduct);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null || !(obj instanceof Vector2D))
      return false;

    Vector2D vector = (Vector2D) obj;
    return this.x == vector.x && this.y == vector.y;
  }

  @Override
  public String toString() {
    return this.x + "i" + " + " + this.y + "j";
  }
}
