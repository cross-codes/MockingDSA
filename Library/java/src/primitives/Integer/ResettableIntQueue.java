package primitives.Integer;

public class ResettableIntQueue {
  private int[] queue;
  private int head, tail;

  public ResettableIntQueue(int n) {
    this.queue = new int[n];
    this.head = this.tail = 0;
  }

  public void resetState() {
    this.head = this.tail = 0;
  }

  public boolean isEmpty() {
    return this.head >= this.tail;
  }

  public void add(int e) {
    this.queue[this.tail] = e;
    this.tail += 1;
  }

  public int poll() {
    int e = this.queue[head];
    head += 1;
    return e;
  }
}
