package collections.trees;

import java.util.Comparator;
import java.util.function.Consumer;

class AVLTreeSet<E> {
  private Item<E> root;
  private final Comparator<? super E> comparator;

  @SuppressWarnings("unchecked")
  public AVLTreeSet() {
    this.comparator = (Comparator<? super E>) Comparator.naturalOrder();
  }

  public AVLTreeSet(Comparator<? super E> cmp) {
    this.comparator = cmp;
  }

  public int size() {
    return root == null ? 0 : root.size;
  }

  public void forEach(Consumer<E> consumer) {
    forEach(root, consumer);
  }

  private void forEach(Item<E> item, Consumer<E> consumer) {
    if (item != null) {
      forEach(item.left, consumer);
      consumer.accept(item.element);
      forEach(item.right, consumer);
    }
  }

  public E findByOrder(int k) {
    Item<E> item = root;
    while (true) {
      int leftSize = (item.left != null) ? item.left.size : 0;

      if (k < leftSize) {
        item = item.left;
      } else if (k > leftSize) {
        k -= (leftSize + 1);
        item = item.right;
      } else {
        return item.element;
      }
    }
  }

  public E lowerBound(E e) {
    Item<E> item = root;
    E result = null;

    while (item != null) {
      int comparison = comparator.compare(e, item.element);
      if (comparison <= 0) {
        result = item.element;
        item = item.left;
      } else {
        item = item.right;
      }
    }
    return result;
  }

  public E upperBound(E e) {
    Item<E> item = root;
    E result = null;

    while (item != null) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0) {
        result = item.element;
        item = item.left;
      } else {
        item = item.right;
      }
    }
    return result;
  }

  public boolean add(E e) {
    if (root == null)
      root = new Item<>(e, null);
    else {
      Item<E> item = root;
      Item<E> child;
      while (true) {
        int comparison = comparator.compare(e, item.element);
        if (comparison < 0) {
          if (item.left == null) {
            item.left = new Item<>(e, item);
            child = item.left;
            break;
          } else
            item = item.left;
        } else if (comparison > 0) {
          if (item.right == null) {
            item.right = new Item<>(e, item);
            child = item.right;
            break;
          } else
            item = item.right;
        } else
          return false;
      }
      while (true) {
        if (item == null)
          return true;
        item.size++;
        if (item.left == child) {
          if (item.balanceFactor == 1) {
            if (child.balanceFactor == 1)
              rotateLL(item, child);
            else
              rotateLR(item, child, child.right);
            item = item.parent;
            break;
          } else if (++item.balanceFactor == 0)
            break;
        } else {
          if (item.balanceFactor == -1) {
            if (child.balanceFactor == -1)
              rotateRR(item, child);
            else
              rotateRL(item, child, child.left);
            item = item.parent;
            break;
          } else if (--item.balanceFactor == 0)
            break;
        }
        child = item;
        item = item.parent;
      }
      for (item = item.parent; item != null; item = item.parent)
        item.size++;
    }
    return true;
  }

  public void remove(E e) {
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0)
        item = item.left;
      else if (comparison > 0)
        item = item.right;
      else {
        remove(item);
        break;
      }
    }
  }

  public int countHigher(E e) {
    int count = 0;
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0) {
        count += item.right == null ? 1 : item.right.size + 1;
        item = item.left;
      } else if (comparison > 0)
        item = item.right;
      else {
        if (item.right != null)
          count += item.right.size;
        break;
      }
    }
    return count;
  }

  public int countLower(E e) {
    int count = 0;
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison > 0) {
        count += item.left == null ? 1 : item.left.size + 1;
        item = item.right;
      } else if (comparison < 0)
        item = item.left;
      else {
        if (item.left != null)
          count += item.left.size;
        break;
      }
    }
    return count;
  }

  private void remove(Item<E> item) {
    if (item.left != null && item.right != null) {
      Item<E> next = item.right;
      while (next.left != null)
        next = next.left;
      item.element = next.element;
      item = next;
    } else if (item == root) {
      if (root.size == 1)
        root = null;
      else {
        root = item.left == null ? item.right : item.left;
        root.parent = null;
      }
      return;
    }
    Item<E> removed = item;
    while (true) {
      Item<E> child = item;
      item = item.parent;
      if (item == null) {
        child = removed.left == null ? removed.right : removed.left;
        if (removed.parent.left == removed)
          removed.parent.left = child;
        else
          removed.parent.right = child;
        if (child != null)
          child.parent = removed.parent;
        return;
      }
      item.size--;
      if (item.left == child) {
        if (item.balanceFactor == -1) {
          child = item.right;
          if (child.balanceFactor == 0) {
            rotateRO(item, child);
            item = child;
            break;
          } else {
            if (child.balanceFactor == -1)
              rotateRR(item, child);
            else
              rotateRL(item, child, child.left);
            item = item.parent;
          }
        } else if (item.balanceFactor-- == 0)
          break;
      } else {
        if (item.balanceFactor == 1) {
          child = item.left;
          if (child.balanceFactor == 0) {
            rotateLO(item, child);
            item = child;
            break;
          } else {
            if (child.balanceFactor == 1)
              rotateLL(item, child);
            else
              rotateLR(item, child, child.right);
            item = item.parent;
          }
        } else if (item.balanceFactor++ == 0)
          break;
      }
    }
    for (item = item.parent; item != null; item = item.parent)
      item.size--;
    Item<E> child = removed.left == null ? removed.right : removed.left;
    if (removed.parent.left == removed)
      removed.parent.left = child;
    else
      removed.parent.right = child;
    if (child != null)
      child.parent = removed.parent;
  }

  private void rotateLL(Item<E> item, Item<E> child) {
    item.balanceFactor = 0;
    child.balanceFactor = 0;
    replaceAsChild(item, child);
    if (child.right == null) {
      child.size = 3;
      item.size = 1;
      item.left = null;
    } else {
      child.size = item.size;
      item.size -= child.left.size + 1;
      setLeft(item, child.right);
    }
    setRight(child, item);
  }

  private void rotateLO(Item<E> item, Item<E> child) {
    item.balanceFactor = 1;
    child.balanceFactor = -1;
    replaceAsChild(item, child);
    child.size = item.size;
    item.size -= child.left.size + 1;
    setLeft(item, child.right);
    setRight(child, item);
  }

  private void rotateLR(Item<E> item, Item<E> child, Item<E> grandchild) {
    replaceAsChild(item, grandchild);
    if (grandchild.balanceFactor == -1) {
      item.balanceFactor = 0;
      child.balanceFactor = 1;
      grandchild.balanceFactor = 0;
      if (grandchild.left == null) {
        grandchild.size = 6;
        item.size = 3;
        child.size = 2;
        setLeft(item, grandchild.right);
        child.right = null;
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    } else if (grandchild.balanceFactor == 0) {
      item.balanceFactor = 0;
      child.balanceFactor = 0;
      if (child.left == null) {
        grandchild.size = 3;
        item.size = 1;
        child.size = 1;
        item.left = null;
        child.right = null;
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    } else {
      item.balanceFactor = -1;
      child.balanceFactor = 0;
      grandchild.balanceFactor = 0;
      if (grandchild.right == null) {
        grandchild.size = 6;
        item.size = 2;
        child.size = 3;
        item.left = null;
        setRight(child, grandchild.left);
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    }
    grandchild.size = item.size;
    item.size -= child.size - grandchild.right.size;
    child.size -= grandchild.right.size + 1;
    setLeft(item, grandchild.right);
    setRight(child, grandchild.left);
    setRight(grandchild, item);
    setLeft(grandchild, child);
  }

  private void rotateRR(Item<E> item, Item<E> child) {
    item.balanceFactor = 0;
    child.balanceFactor = 0;
    replaceAsChild(item, child);
    if (child.left == null) {
      child.size = 3;
      item.size = 1;
      item.right = null;
    } else {
      child.size = item.size;
      item.size -= child.right.size + 1;
      setRight(item, child.left);
    }
    setLeft(child, item);
  }

  private void rotateRO(Item<E> item, Item<E> child) {
    item.balanceFactor = -1;
    child.balanceFactor = 1;
    replaceAsChild(item, child);
    child.size = item.size;
    item.size -= child.right.size + 1;
    setRight(item, child.left);
    setLeft(child, item);
  }

  private void rotateRL(Item<E> item, Item<E> child, Item<E> grandchild) {
    replaceAsChild(item, grandchild);
    if (grandchild.balanceFactor == 1) {
      item.balanceFactor = 0;
      child.balanceFactor = -1;
      grandchild.balanceFactor = 0;
      if (grandchild.right == null) {
        grandchild.size = 6;
        item.size = 3;
        child.size = 2;
        setRight(item, grandchild.left);
        child.left = null;
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    } else if (grandchild.balanceFactor == 0) {
      item.balanceFactor = 0;
      child.balanceFactor = 0;
      if (child.right == null) {
        grandchild.size = 3;
        item.size = 1;
        child.size = 1;
        item.right = null;
        child.left = null;
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    } else {
      item.balanceFactor = 1;
      child.balanceFactor = 0;
      grandchild.balanceFactor = 0;
      if (grandchild.left == null) {
        grandchild.size = 6;
        item.size = 2;
        child.size = 3;
        item.right = null;
        setLeft(child, grandchild.right);
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    }
    grandchild.size = item.size;
    item.size -= child.size - grandchild.left.size;
    child.size -= grandchild.left.size + 1;
    setRight(item, grandchild.left);
    setLeft(child, grandchild.right);
    setLeft(grandchild, item);
    setRight(grandchild, child);
  }

  private void replaceAsChild(Item<E> oldItem, Item<E> newItem) {
    Item<E> parent = oldItem.parent;
    if (parent == null)
      root = newItem;
    else if (parent.left == oldItem)
      parent.left = newItem;
    else
      parent.right = newItem;
    newItem.parent = parent;
  }

  private void setLeft(Item<E> item, Item<E> child) {
    item.left = child;
    child.parent = item;
  }

  private void setRight(Item<E> item, Item<E> child) {
    item.right = child;
    child.parent = item;
  }

  private static class Item<E> {
    private E element;
    private Item<E> parent;
    private Item<E> left;
    private Item<E> right;
    private int balanceFactor;
    private int size = 1;

    private Item(E element, Item<E> parent) {
      this.element = element;
      this.parent = parent;
    }
  }
}
