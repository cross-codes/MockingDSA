package collections;

import java.util.ArrayDeque;
import java.util.function.BinaryOperator;

import collections.tuples.OrderedPair;

public class AggregateQueue<E extends Comparable<E>> {
  private BinaryOperator<E> function;
  private AggregateStack in, out;

  public AggregateQueue(BinaryOperator<E> function) {
    this.function = function;
    this.in = new AggregateStack();
    this.out = new AggregateStack();
  }

  void add(E e) {
    in.add(e);
  }

  void poll() {
    if (out.stack.isEmpty()) {
      while (!in.stack.isEmpty()) {
        E val = in.stack.peekLast().first;
        in.pop();
        out.add(val);
      }
    }

    out.pop();
  }

  E query() {
    if (in.stack.isEmpty()) {
      return out.aggregate();
    }

    if (out.stack.isEmpty()) {
      return in.aggregate();
    }

    return function.apply(in.aggregate(), out.aggregate());
  }

  private class AggregateStack {
    public ArrayDeque<OrderedPair<E, E>> stack;

    public AggregateStack() {
      this.stack = new ArrayDeque<>();
    }

    void add(E x) {
      E currAgg = stack.isEmpty() ? x : function.apply(stack.peekLast().second, x);
      stack.addLast(new OrderedPair<>(x, currAgg));
    }

    void pop() {
      stack.removeLast();
    }

    E aggregate() {
      return stack.peekLast().second;
    }
  }
}
