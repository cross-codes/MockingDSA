using System.Numerics;

namespace Evermore.Collections.Ranged;

public class StaticPrefixSum<T> where T : IBinaryInteger<T>
{
    private long[] _prefix;
    public StaticPrefixSum(T[] array)
    {
        _prefix = new long[array.Length + 1];

        for (int i = 1; i <= array.Length; i++)
        {
            long currentVal = long.CreateChecked(array[i - 1]);
            _prefix[i] = _prefix[i - 1] + currentVal;
        }
    }

    public long RangeSum(int a, int b)
    {
        return _prefix[b] - _prefix[a];
    }
}
