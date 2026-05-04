namespace Evermore.Collections.Ranged;

using System.Numerics;

public class DifferenceArray<T> where T : IBinaryInteger<T>
{
    private readonly T[] _diff;
    private readonly SegmentTree<T> _tree;
    public DifferenceArray(T[] array)
    {
        _diff = new T[array.Length + 1];
        _diff[0] = array[0];

        for (int i = 1; i < array.Length; i++)
        {
            _diff[i] = array[i] - array[i - 1];
        }
        _tree = new SegmentTree<T>((a, b) => a + b, _diff, T.Zero);
    }

    public void IncreaseInRange(int a, int b, T x)
    {
        _diff[a] += x;
        _tree.SetAtIndex(a, _diff[a]);

        _diff[b] -= x;
        _tree.SetAtIndex(b, _diff[b]);
    }

    public T GetUnderlyingValue(int index)
    {
        return _tree.RangeQuery(0, index + 1);
    }
}
