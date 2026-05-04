namespace _327;

public class Solution
{
    public int CountRangeSum(int[] nums, int lower, int upper)
    {
        int n = nums.Length, cnt = 0, gcnt = 0;

        long sum = 0;
        AVLTreeSet<(long e, int _)> ost = new();
        ost.Add((0, gcnt++));
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            cnt += ost.CountLower((sum - lower, int.MaxValue)) - ost.CountLower((sum - upper, int.MinValue));
            ost.Add((sum, gcnt++));
        }

        return cnt;
    }
}

class AVLTreeSet<E>
{
    private Item<E>? root;
    private readonly IComparer<E> comparator;

    public AVLTreeSet()
    {
        this.comparator = Comparer<E>.Default;
    }

    public AVLTreeSet(IComparer<E> cmp)
    {
        this.comparator = cmp ?? throw new ArgumentNullException(nameof(cmp));
    }

    public int Size()
    {
        return root?.size ?? 0;
    }

    public void ForEach(Action<E> consumer)
    {
        if (consumer == null) throw new ArgumentNullException(nameof(consumer));
        ForEach(root, consumer);
    }

    private void ForEach(Item<E>? item, Action<E> consumer)
    {
        if (item != null)
        {
            ForEach(item.left, consumer);
            consumer(item.element);
            ForEach(item.right, consumer);
        }
    }

    public E? FindByOrder(int k)
    {
        Item<E>? item = root;
        while (item != null)
        {
            int leftSize = item.left?.size ?? 0;

            if (k < leftSize)
            {
                item = item.left;
            }
            else if (k > leftSize)
            {
                k -= (leftSize + 1);
                item = item.right;
            }
            else
            {
                return item.element;
            }
        }
        return default;
    }

    public E? LowerBound(E e)
    {
        Item<E>? item = root;
        E? result = default;

        while (item != null)
        {
            int comparison = comparator.Compare(e, item.element);
            if (comparison <= 0)
            {
                result = item.element;
                item = item.left;
            }
            else
            {
                item = item.right;
            }
        }
        return result;
    }

    public E? UpperBound(E e)
    {
        Item<E>? item = root;
        E? result = default;

        while (item != null)
        {
            int comparison = comparator.Compare(e, item.element);
            if (comparison < 0)
            {
                result = item.element;
                item = item.left;
            }
            else
            {
                item = item.right;
            }
        }
        return result;
    }

    public bool Add(E e)
    {
        if (root == null)
        {
            root = new Item<E>(e, null);
            return true;
        }

        Item<E>? item = root;
        Item<E> child;

        while (true)
        {
            if (item == null) return false;

            int comparison = comparator.Compare(e, item.element);
            if (comparison < 0)
            {
                if (item.left == null)
                {
                    item.left = new Item<E>(e, item);
                    child = item.left;
                    break;
                }
                else
                    item = item.left;
            }
            else if (comparison > 0)
            {
                if (item.right == null)
                {
                    item.right = new Item<E>(e, item);
                    child = item.right;
                    break;
                }
                else
                    item = item.right;
            }
            else
                return false;
        }

        while (item != null)
        {
            item.size++;
            if (item.left == child)
            {
                if (item.balanceFactor == 1)
                {
                    if (child.balanceFactor == 1)
                        RotateLL(item, child);
                    else
                        RotateLR(item, child, child.right);
                    item = item.parent;
                    break;
                }
                else if (++item.balanceFactor == 0)
                    break;
            }
            else
            {
                if (item.balanceFactor == -1)
                {
                    if (child.balanceFactor == -1)
                        RotateRR(item, child);
                    else
                        RotateRL(item, child, child.left);
                    item = item.parent;
                    break;
                }
                else if (--item.balanceFactor == 0)
                    break;
            }
            child = item;
            item = item.parent;
        }

        for (Item<E>? curr = item?.parent; curr != null; curr = curr.parent)
        {
            curr.size++;
        }

        return true;
    }

    public void Remove(E e)
    {
        for (Item<E>? item = root; item != null;)
        {
            int comparison = comparator.Compare(e, item.element);
            if (comparison < 0)
                item = item.left;
            else if (comparison > 0)
                item = item.right;
            else
            {
                RemoveItem(item);
                break;
            }
        }
    }

    public int CountHigher(E e)
    {
        int count = 0;
        for (Item<E>? item = root; item != null;)
        {
            int comparison = comparator.Compare(e, item.element);
            if (comparison < 0)
            {
                count += (item.right?.size ?? 0) + 1;
                item = item.left;
            }
            else if (comparison > 0)
                item = item.right;
            else
            {
                count += item.right?.size ?? 0;
                break;
            }
        }
        return count;
    }

    public int CountLower(E e)
    {
        int count = 0;
        for (Item<E>? item = root; item != null;)
        {
            int comparison = comparator.Compare(e, item.element);
            if (comparison > 0)
            {
                count += (item.left?.size ?? 0) + 1;
                item = item.right;
            }
            else if (comparison < 0)
                item = item.left;
            else
            {
                count += item.left?.size ?? 0;
                break;
            }
        }
        return count;
    }

    private void RemoveItem(Item<E>? item)
    {
        if (item == null) return;

        if (item.left != null && item.right != null)
        {
            Item<E> next = item.right;
            while (next.left != null)
                next = next.left;
            item.element = next.element;
            item = next;
        }
        else if (item == root)
        {
            if (root.size == 1)
                root = null;
            else
            {
                root = item.left ?? item.right;
                if (root != null) root.parent = null;
            }
            return;
        }

        Item<E> removed = item;
        while (item != null)
        {
            Item<E> child = item;
            item = item.parent;
            if (item == null)
            {
                Item<E>? tempChild = removed.left ?? removed.right;
                if (removed.parent != null)
                {
                    if (removed.parent.left == removed)
                        removed.parent.left = tempChild;
                    else
                        removed.parent.right = tempChild;
                }
                if (tempChild != null)
                    tempChild.parent = removed.parent;
                return;
            }

            item.size--;
            if (item.left == child)
            {
                if (item.balanceFactor == -1)
                {
                    Item<E>? rightChild = item.right;
                    if (rightChild == null) break;

                    if (rightChild.balanceFactor == 0)
                    {
                        RotateRO(item, rightChild);
                        item = rightChild;
                        break;
                    }
                    else
                    {
                        if (rightChild.balanceFactor == -1)
                            RotateRR(item, rightChild);
                        else
                            RotateRL(item, rightChild, rightChild.left);
                        item = item.parent;
                    }
                }
                else if (item.balanceFactor-- == 0)
                    break;
            }
            else
            {
                if (item.balanceFactor == 1)
                {
                    Item<E>? leftChild = item.left;
                    if (leftChild == null) break;

                    if (leftChild.balanceFactor == 0)
                    {
                        RotateLO(item, leftChild);
                        item = leftChild;
                        break;
                    }
                    else
                    {
                        if (leftChild.balanceFactor == 1)
                            RotateLL(item, leftChild);
                        else
                            RotateLR(item, leftChild, leftChild.right);
                        item = item.parent;
                    }
                }
                else if (item.balanceFactor++ == 0)
                    break;
            }
        }

        for (Item<E>? curr = item?.parent; curr != null; curr = curr.parent)
            curr.size--;

        Item<E>? finalChildNode = removed.left ?? removed.right;
        if (removed.parent != null)
        {
            if (removed.parent.left == removed)
                removed.parent.left = finalChildNode;
            else
                removed.parent.right = finalChildNode;
        }

        if (finalChildNode != null)
            finalChildNode.parent = removed.parent;
    }

    private void RotateLL(Item<E>? item, Item<E>? child)
    {
        if (item == null || child == null) return;

        item.balanceFactor = 0;
        child.balanceFactor = 0;
        ReplaceAsChild(item, child);

        if (child.right == null)
        {
            child.size = 3;
            item.size = 1;
            item.left = null;
        }
        else
        {
            child.size = item.size;
            item.size -= (child.left?.size ?? 0) + 1;
            SetLeft(item, child.right);
        }
        SetRight(child, item);
    }

    private void RotateLO(Item<E>? item, Item<E>? child)
    {
        if (item == null || child == null) return;

        item.balanceFactor = 1;
        child.balanceFactor = -1;
        ReplaceAsChild(item, child);
        child.size = item.size;
        item.size -= (child.left?.size ?? 0) + 1;
        SetLeft(item, child.right);
        SetRight(child, item);
    }

    private void RotateLR(Item<E>? item, Item<E>? child, Item<E>? grandchild)
    {
        if (item == null || child == null || grandchild == null) return;

        ReplaceAsChild(item, grandchild);
        if (grandchild.balanceFactor == -1)
        {
            item.balanceFactor = 0;
            child.balanceFactor = 1;
            grandchild.balanceFactor = 0;
            if (grandchild.left == null)
            {
                grandchild.size = 6;
                item.size = 3;
                child.size = 2;
                SetLeft(item, grandchild.right);
                child.right = null;
                SetRight(grandchild, item);
                SetLeft(grandchild, child);
                return;
            }
        }
        else if (grandchild.balanceFactor == 0)
        {
            item.balanceFactor = 0;
            child.balanceFactor = 0;
            if (child.left == null)
            {
                grandchild.size = 3;
                item.size = 1;
                child.size = 1;
                item.left = null;
                child.right = null;
                SetRight(grandchild, item);
                SetLeft(grandchild, child);
                return;
            }
        }
        else
        {
            item.balanceFactor = -1;
            child.balanceFactor = 0;
            grandchild.balanceFactor = 0;
            if (grandchild.right == null)
            {
                grandchild.size = 6;
                item.size = 2;
                child.size = 3;
                item.left = null;
                SetRight(child, grandchild.left);
                SetRight(grandchild, item);
                SetLeft(grandchild, child);
                return;
            }
        }

        grandchild.size = item.size;
        item.size -= child.size - (grandchild.right?.size ?? 0);
        child.size -= (grandchild.right?.size ?? 0) + 1;
        SetLeft(item, grandchild.right);
        SetRight(child, grandchild.left);
        SetRight(grandchild, item);
        SetLeft(grandchild, child);
    }

    private void RotateRR(Item<E>? item, Item<E>? child)
    {
        if (item == null || child == null) return;

        item.balanceFactor = 0;
        child.balanceFactor = 0;
        ReplaceAsChild(item, child);
        if (child.left == null)
        {
            child.size = 3;
            item.size = 1;
            item.right = null;
        }
        else
        {
            child.size = item.size;
            item.size -= (child.right?.size ?? 0) + 1;
            SetRight(item, child.left);
        }
        SetLeft(child, item);
    }

    private void RotateRO(Item<E>? item, Item<E>? child)
    {
        if (item == null || child == null) return;

        item.balanceFactor = -1;
        child.balanceFactor = 1;
        ReplaceAsChild(item, child);
        child.size = item.size;
        item.size -= (child.right?.size ?? 0) + 1;
        SetRight(item, child.left);
        SetLeft(child, item);
    }

    private void RotateRL(Item<E>? item, Item<E>? child, Item<E>? grandchild)
    {
        if (item == null || child == null || grandchild == null) return;

        ReplaceAsChild(item, grandchild);
        if (grandchild.balanceFactor == 1)
        {
            item.balanceFactor = 0;
            child.balanceFactor = -1;
            grandchild.balanceFactor = 0;
            if (grandchild.right == null)
            {
                grandchild.size = 6;
                item.size = 3;
                child.size = 2;
                SetRight(item, grandchild.left);
                child.left = null;
                SetLeft(grandchild, item);
                SetRight(grandchild, child);
                return;
            }
        }
        else if (grandchild.balanceFactor == 0)
        {
            item.balanceFactor = 0;
            child.balanceFactor = 0;
            if (child.right == null)
            {
                grandchild.size = 3;
                item.size = 1;
                child.size = 1;
                item.right = null;
                child.left = null;
                SetLeft(grandchild, item);
                SetRight(grandchild, child);
                return;
            }
        }
        else
        {
            item.balanceFactor = 1;
            child.balanceFactor = 0;
            grandchild.balanceFactor = 0;
            if (grandchild.left == null)
            {
                grandchild.size = 6;
                item.size = 2;
                child.size = 3;
                item.right = null;
                SetLeft(child, grandchild.right);
                SetLeft(grandchild, item);
                SetRight(grandchild, child);
                return;
            }
        }

        grandchild.size = item.size;
        item.size -= child.size - (grandchild.left?.size ?? 0);
        child.size -= (grandchild.left?.size ?? 0) + 1;
        SetRight(item, grandchild.left);
        SetLeft(child, grandchild.right);
        SetLeft(grandchild, item);
        SetRight(grandchild, child);
    }

    private void ReplaceAsChild(Item<E> oldItem, Item<E> newItem)
    {
        Item<E>? parent = oldItem.parent;
        if (parent == null)
            root = newItem;
        else if (parent.left == oldItem)
            parent.left = newItem;
        else
            parent.right = newItem;
        newItem.parent = parent;
    }

    private void SetLeft(Item<E> item, Item<E>? child)
    {
        item.left = child;
        if (child != null) child.parent = item;
    }

    private void SetRight(Item<E> item, Item<E>? child)
    {
        item.right = child;
        if (child != null) child.parent = item;
    }

    private class Item<T>
    {
        public T element;
        public Item<T>? parent;
        public Item<T>? left;
        public Item<T>? right;
        public int balanceFactor;
        public int size = 1;

        public Item(T element, Item<T>? parent)
        {
            this.element = element;
            this.parent = parent;
        }
    }
}
