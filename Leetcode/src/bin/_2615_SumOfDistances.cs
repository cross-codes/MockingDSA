namespace _2615;

using System.Numerics;
using System.Linq;

public class Solution
{
    public long[] Distance(int[] nums)
    {
        int n = nums.Length;
        Dictionary<int, (List<int> indexes, StaticPrefixSum<int>? prefix)> map = new();
        for (int i = 0; i < n; i++)
        {
            int e = nums[i];
            if (map.ContainsKey(e))
            {
                map[e].indexes.Add(i);
            }
            else
            {
                List<int> indexList = new();
                indexList.Add(i);
                map.Add(e, (indexList, null));
            }
        }

        var keys = map.Keys.ToList();
        foreach (int key in keys)
        {
            map[key] = (map[key].indexes, new(map[key].indexes));
        }

        long[] res = new long[n];
        for (int i = 0; i < n; i++)
        {
            int e = nums[i];
            var (indexes, prefix) = map[e];
            int pos = indexes.BinarySearch(i);
            int len = indexes.Count;

            long prior = pos * (long)i - prefix!.RangeSum(0, pos);
            long post = prefix!.RangeSum(pos + 1, len) - (len - pos - 1) * (long)(i);
            res[i] = prior + post;
        }


        return res;
    }
}

class StaticPrefixSum<T> where T : IBinaryInteger<T>
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

    public StaticPrefixSum(List<T> array)
    {
        _prefix = new long[array.Count + 1];

        for (int i = 1; i <= array.Count; i++)
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
