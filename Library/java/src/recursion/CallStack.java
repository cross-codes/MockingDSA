package recursion;

class CallStack {
  private final int[] stage;
  private final int[] from;
  private final int[] to;
  private final int[] helper;
  private final int[] height;
  private int pointer = -1;

  public CallStack(int n) {
    stage = new int[n];
    from = new int[n];
    to = new int[n];
    helper = new int[n];
    height = new int[n];
  }

  public void call(int from, int to, int helper, int height, Procedure... procedures) {
    stage[++pointer] = 0;
    this.from[pointer] = from;
    this.to[pointer] = to;
    this.helper[pointer] = helper;
    this.height[pointer] = height;
    while (pointer >= 0)
      procedures[stage[pointer]].apply(this.from[pointer], this.to[pointer], this.helper[pointer],
          this.height[pointer]);
  }

  public void pushAndAdvance(int from, int to, int helper, int height) {
    stage[pointer++]++;
    stage[pointer] = 0;
    this.from[pointer] = from;
    this.to[pointer] = to;
    this.helper[pointer] = helper;
    this.height[pointer] = height;
  }

  public void pushAndLoop(int from, int to, int helper, int height) {
    stage[++pointer] = 0;
    this.from[pointer] = from;
    this.to[pointer] = to;
    this.helper[pointer] = helper;
    this.height[pointer] = height;
  }

  public int setFrom(int from) {
    return this.from[pointer] = from;
  }

  public int setTo(int to) {
    return this.to[pointer] = to;
  }

  public int setHelper(int helper) {
    return this.helper[pointer] = helper;
  }

  public int setHeight(int height) {
    return this.height[pointer] = height;
  }

  public void ret() {
    pointer--;
  }

  public interface Procedure {
    void apply(int from, int to, int helper, int height);
  }
}
