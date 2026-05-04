namespace Evermore.Collections.Ranged;

using System;
using System.Collections.Generic;

public class ExplicitTreapNode<T> where T : IComparable<T>
{
    public T Value { get; set; }
    public int Priority { get; set; }
    public int Size { get; set; }

    public ExplicitTreapNode<T>? Left { get; set; }
    public ExplicitTreapNode<T>? Right { get; set; }

    public ExplicitTreapNode(T value)
    {
        Value = value;
        Priority = Random.Shared.Next();
        Size = 1;
    }
}

public class ExplicitTreap<T> where T : IComparable<T>
{
    private ExplicitTreapNode<T>? _root;
    private int GetSize(ExplicitTreapNode<T>? node) => node?.Size ?? 0;

    private void UpdateSize(ExplicitTreapNode<T>? node)
    {
        if (node != null)
        {
            node.Size = 1 + GetSize(node.Left) + GetSize(node.Right);
        }
    }

    private void Split(ExplicitTreapNode<T>? node, T k, out ExplicitTreapNode<T>? left, out ExplicitTreapNode<T>? right)
    {
        if (node == null)
        {
            left = right = null;
            return;
        }

        if (node.Value.CompareTo(k) <= 0)
        {
            Split(node.Right, k, out ExplicitTreapNode<T>? rightOfLeft, out right);
            node.Right = rightOfLeft;
            left = node;
        }
        else
        {
            Split(node.Left, k, out left, out ExplicitTreapNode<T>? leftOfRight);
            node.Left = leftOfRight;
            right = node;
        }
        UpdateSize(node);
    }

    private void SplitStrict(ExplicitTreapNode<T>? node, T k, out ExplicitTreapNode<T>? left, out ExplicitTreapNode<T>? right)
    {
        if (node == null)
        {
            left = right = null;
            return;
        }

        if (node.Value.CompareTo(k) < 0)
        {
            SplitStrict(node.Right, k, out ExplicitTreapNode<T>? rightOfLeft, out right);
            node.Right = rightOfLeft;
            left = node;
        }
        else
        {
            SplitStrict(node.Left, k, out left, out ExplicitTreapNode<T>? leftOfRight);
            node.Left = leftOfRight;
            right = node;
        }
        UpdateSize(node);
    }

    private ExplicitTreapNode<T>? Merge(ExplicitTreapNode<T>? left, ExplicitTreapNode<T>? right)
    {
        if (left == null) return right;
        if (right == null) return left;

        if (left.Priority > right.Priority)
        {
            left.Right = Merge(left.Right, right);
            UpdateSize(left);
            return left;
        }
        else
        {
            right.Left = Merge(left, right.Left);
            UpdateSize(right);
            return right;
        }
    }

    public int Count => GetSize(_root);
    public void Insert(T value)
    {
        ExplicitTreapNode<T> newNode = new ExplicitTreapNode<T>(value);
        Split(_root, value, out ExplicitTreapNode<T>? left, out ExplicitTreapNode<T>? right);
        _root = Merge(Merge(left, newNode), right);
    }

    public bool RemoveAll(T value)
    {
        if (this.Count <= 0)
        {
            return false;
        }

        SplitStrict(_root, value, out ExplicitTreapNode<T>? less, out ExplicitTreapNode<T>? greaterOrEqual);
        Split(greaterOrEqual, value, out ExplicitTreapNode<T>? target, out ExplicitTreapNode<T>? greater);
        _root = Merge(less, greater);
        return true;
    }

    public bool RemoveAllInRange(T min, T max)
    {
        if (this.Count <= 0)
        {
            return false;
        }

        if (min.CompareTo(max) > 0) return false;
        SplitStrict(_root, min, out ExplicitTreapNode<T>? less, out ExplicitTreapNode<T>? greaterOrEqual);
        Split(greaterOrEqual, max, out ExplicitTreapNode<T>? toRemove, out ExplicitTreapNode<T>? greater);
        bool removed = toRemove != null;
        _root = Merge(less, greater);
        return removed;
    }

    public bool Contains(T value)
    {
        ExplicitTreapNode<T>? current = _root;
        while (current != null)
        {
            int cmp = value.CompareTo(current.Value);
            if (cmp == 0) return true;
            current = cmp < 0 ? current.Left : current.Right;
        }
        return false;
    }

    public T KthSmallestOneIndexed(int index)
    {
        index -= 1;
        ExplicitTreapNode<T>? current = _root;
        while (current != null)
        {
            int leftSize = GetSize(current.Left);
            if (index == leftSize) return current.Value;

            if (index < leftSize)
            {
                current = current.Left;
            }
            else
            {
                current = current.Right;
                index -= (leftSize + 1);
            }
        }
        throw new InvalidOperationException("KthSmallestOneIndexed()");
    }

    public IEnumerable<T> GetSortedElements()
    {
        var stack = new Stack<ExplicitTreapNode<T>>();
        var current = _root;

        while (stack.Count > 0 || current != null)
        {
            if (current != null)
            {
                stack.Push(current);
                current = current.Left;
            }
            else
            {
                current = stack.Pop();
                yield return current.Value;
                current = current.Right;
            }
        }
    }
}
