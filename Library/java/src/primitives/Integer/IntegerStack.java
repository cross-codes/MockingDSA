package primitives.Integer;

import java.util.Arrays;
import java.util.EmptyStackException;

public class IntegerStack {

  private int[] stack;
  private final boolean isUnbound;
  private int STACK_SIZE;
  private int pos = -1;

  public IntegerStack(int initialSize, boolean isUnbound) {
    if (initialSize <= -1)
      throw new IllegalArgumentException();
    this.STACK_SIZE = initialSize;
    this.stack = new int[this.STACK_SIZE];
    this.isUnbound = isUnbound;
  }

  public void push(int element) {
    if (!this.isUnbound && this.pos >= this.STACK_SIZE - 1)
      throw new IllegalStateException();
    this.ensureCapacity();
    this.stack[++this.pos] = element;
  }

  public int pop() {
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
    Arrays.fill(this.stack, 0);
    this.pos = -1;
  }

  public int peek() {
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
        int[] newStack = new int[this.STACK_SIZE << 1];
        System.arraycopy(this.stack, 0, newStack, 0, this.STACK_SIZE);
        this.stack = newStack;
        this.STACK_SIZE <<= 1;
      }
    }
  }
}
