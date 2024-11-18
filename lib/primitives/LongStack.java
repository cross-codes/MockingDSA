package primitives;

import java.util.Arrays;
import java.util.EmptyStackException;

public class LongStack {

  private long[] stack;
  private final boolean isUnbound;
  private int STACK_SIZE;
  private int pos = -1;

  public LongStack(int initialSize, boolean isUnbound) {
    if (initialSize <= -1)
      throw new IllegalArgumentException();
    this.STACK_SIZE = initialSize;
    this.stack = new long[this.STACK_SIZE];
    this.isUnbound = isUnbound;
  }

  public void push(long element) {
    if (!this.isUnbound && this.pos >= this.STACK_SIZE - 1)
      throw new IllegalStateException();
    this.ensureCapacity();
    this.stack[++this.pos] = element;
  }

  public long pop() {
    if (this.pos == -1)
      throw new EmptyStackException();
    return this.stack[this.pos--];
  }

  public boolean isEmpty() {
    return this.pos == -1;
  }

  public int size() {
    return this.pos + 1;
  }

  public void clear() {
    Arrays.fill(this.stack, 0L);
    this.pos = -1;
  }

  public long peek() {
    if (this.pos == -1)
      throw new EmptyStackException();
    return this.stack[this.pos];
  }

  @Override
  public String toString() {
    final StringBuilder sb = new StringBuilder("[");
    for (int i = 0; i <= this.pos; i++)
      sb.append(this.stack[i]).append(i == this.pos ? "" : ", ");
    return sb.append("]").toString();
  }

  private void ensureCapacity() {
    if (this.isUnbound) {
      if (pos == this.STACK_SIZE - 1) {
        long[] newStack = new long[this.STACK_SIZE << 1];
        System.arraycopy(this.stack, 0, newStack, 0, this.STACK_SIZE);
        this.stack = newStack;
        this.STACK_SIZE <<= 1;
      }
    }
  }
}