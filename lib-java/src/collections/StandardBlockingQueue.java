package collections;

public class StandardBlockingQueue<E> {

  private E[] queue;
  private int QUEUE_SIZE;
  public int headPos = -1;
  private int endPos = 0;

  @SuppressWarnings("unchecked")
  public StandardBlockingQueue(int initialSize) {
    if (initialSize <= -1)
      throw new IllegalArgumentException();
    this.QUEUE_SIZE = initialSize;
    this.queue = (E[]) new Object[this.QUEUE_SIZE];
  }

  public boolean add(E element) {
    if (this.headPos == -1) {
      this.headPos = 0;
      this.queue[endPos++ % this.QUEUE_SIZE] = element;
      return true;
    } else if (this.headPos % this.QUEUE_SIZE != this.endPos % this.QUEUE_SIZE) {
      this.queue[endPos++ % this.QUEUE_SIZE] = element;
      return true;
    } else
      return false;
  }

  public E poll() {
    E element = this.queue[this.headPos % this.QUEUE_SIZE];
    this.queue[this.headPos++ % this.QUEUE_SIZE] = null;
    if (this.headPos % this.QUEUE_SIZE == this.endPos % this.QUEUE_SIZE) {
      this.headPos = -1;
      this.endPos = 0;
    }
    return element;
  }

  public E peek() {
    return this.queue[this.headPos % this.QUEUE_SIZE];
  }
}