namespace Evermore.Collections;

using System;

public class IndexCompress<T> where T : IComparable<T>
{
    private readonly T[] _arr;
    private readonly int _size;

    public IndexCompress(T[] vec)
    {
        _arr = (T[])vec.Clone();
        Array.Sort(_arr);

        int unique = 0;
        if (_arr.Length > 0)
        {
            unique = 1;
            for (int i = 1; i < _arr.Length; i++)
            {
                if (_arr[i].CompareTo(_arr[i - 1]) != 0)
                {
                    _arr[unique++] = _arr[i];
                }
            }
        }

        _size = unique;
    }

    public int GetCompressedIndex(T value)
    {
        int index = Array.BinarySearch(_arr, 0, _size, value);
        return index >= 0 ? index : ~index;
    }

    public int GetMaxRange()
    {
        return _size - 1;
    }

    public T GetOriginalValue(int compressedIndex)
    {
        if (compressedIndex < 0 || compressedIndex >= _size)
            throw new ArgumentOutOfRangeException(nameof(compressedIndex));

        return _arr[compressedIndex];
    }
}
