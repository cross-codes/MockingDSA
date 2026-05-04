namespace Evermore.Collections.Ranged;

using System;
using System.Numerics;

public class SegmentTree<T>
{
    private readonly int _n;
    private readonly int _offset;
    private readonly T[] _tree;
    private readonly Func<T, T, T> _function;
    private readonly T _defaultValue;

    public SegmentTree(Func<T, T, T> function, T[] array, T _defaultValue)
    {
        _n = array.Length;
        this._function = function;
        this._defaultValue = _defaultValue;
        _offset = _n <= 1 ? 1 : 1 << (32 - BitOperations.LeadingZeroCount((uint)_n - 1));

        _tree = new T[_offset << 1];
        Array.Fill(_tree, _defaultValue);

        Array.Copy(array, 0, _tree, _offset, _n);
        for (int i = _offset - 1; i > 0; i--)
        {
            _tree[i] = _function(_tree[i << 1], _tree[(i << 1) | 1]);
        }
    }

    public void SetAtIndex(int index, T value)
    {
        if (index < 0 || index >= _n)
            throw new ArgumentOutOfRangeException(nameof(index));

        index += _offset;
        _tree[index] = value;

        while (index > 1)
        {
            _tree[index >> 1] = _function(_tree[index], _tree[index ^ 1]);
            index >>= 1;
        }
    }

    public T RangeQuery(int a, int b)
    {
        a += _offset;
        b += _offset;

        T result = _defaultValue;
        while (a < b)
        {
            if ((a & 1) != 0)
            {
                result = _function(result, _tree[a++]);
            }
            if ((b & 1) != 0)
            {
                result = _function(result, _tree[--b]);
            }

            a >>= 1;
            b >>= 1;
        }

        return result;
    }
}
