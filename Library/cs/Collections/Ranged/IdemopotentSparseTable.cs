namespace Evermore.Collections.Ranged;

using System;
using System.Numerics;

public class IdempotentSparseTable<T>
{
    private readonly Func<T, T, T> _function;
    private readonly T[][] _table;
    private readonly int _n;

    public IdempotentSparseTable(T[] array, Func<T, T, T> func)
    {
        _function = func;
        _n = array.Length;

        if (_n == 0)
        {
            _table = Array.Empty<T[]>();
            return;
        }

        int K = BitOperations.Log2((uint)_n);
        _table = new T[K + 1][];
        for (int i = 0; i <= K; i++)
        {
            _table[i] = new T[this._n];
        }

        Array.Copy(array, _table[0], this._n);
        for (int y = 1; y <= K; y++)
        {
            int step = 1 << (y - 1);
            for (int x = 0; x <= _n - (1 << y); x++)
            {
                _table[y][x] = _function(_table[y - 1][x], _table[y - 1][x + step]);
            }
        }
    }

    public T RangeQuery(int a, int b)
    {
        int row = BitOperations.Log2((uint)(b - a));
        return _function(_table[row][a], _table[row][b - (1 << row)]);
    }
}
