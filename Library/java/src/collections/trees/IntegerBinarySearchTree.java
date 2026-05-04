package collections.trees;

public final class IntegerBinarySearchTree {
  private Node root;
  private final Node[] leaves;

  public IntegerBinarySearchTree(int n) {
    leaves = new Node[Integer.highestOneBit(n) << 1];
    for (int i = 0; i < leaves.length; i++)
      leaves[i] = new Node(null, null, 0);
  }

  public void set(int element) {
    leaves[element].value = 1;
  }

  public void build() {
    Node[] nodes = leaves;
    while (nodes.length != 1) {
      Node[] newNodes = new Node[nodes.length / 2];
      for (int i = 0; i < newNodes.length; i++) {
        Node left = nodes[i * 2];
        Node right = nodes[i * 2 + 1];
        newNodes[i] = new Node(left, right, left.value + right.value);
        left.parent = right.parent = newNodes[i];
      }
      nodes = newNodes;
    }
    root = nodes[0];
  }

  public int size() {
    return root.value;
  }

  public boolean contains(int element) {
    return leaves[element].value != 0;
  }

  public int orderOfKey(int x) {
    int index = 0;
    for (Node node = leaves[x]; node != root; node = node.parent) {
      if (node.parent.right == node)
        index += node.parent.left.value;
    }
    return leaves[x].value == 0 ? -index - 1 : index;
  }

  public void add(int element) {
    for (Node node = leaves[element]; node != null; node = node.parent)
      node.value++;
  }

  public void removeOne(int element) {
    for (Node node = leaves[element]; node != null; node = node.parent)
      node.value--;
  }

  public int findByOrder(int k) {
    int element = 0;
    int step = leaves.length / 2;
    for (Node node = root; node.left != null; step >>= 1) {
      if (k < node.left.value)
        node = node.left;
      else {
        k -= node.left.value;
        element += step;
        node = node.right;
      }
    }
    return element;
  }

  private static class Node {
    private Node parent;
    private final Node left;
    private final Node right;
    private int value;

    private Node(Node left, Node right, int value) {
      this.left = left;
      this.right = right;
      this.value = value;
    }
  }
}
