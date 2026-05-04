namespace Evermore.Collections.Ranged;

using System;
using System.Numerics;

public class WaveletMatrix
{
    private readonly int _levels;
    private readonly int[][] _pref;
    private readonly int[] _zeroBoundary;

    public WaveletMatrix(int[] arr, int maxVal)
    {
        int n = arr.Length;
        _levels = 32 - BitOperations.LeadingZeroCount((uint)Math.Max(1, maxVal));

        _pref = new int[_levels][];
        for (int i = 0; i < _levels; i++)
        {
            _pref[i] = new int[n + 1];
        }

        _zeroBoundary = new int[_levels];

        int[] temp = new int[n];
        int[] workingArr = (int[])arr.Clone();

        for (int l = _levels - 1; l >= 0; l--)
        {
            int bit = 1 << l;
            int zeros = 0;

            for (int i = 0; i < n; i++)
            {
                if ((workingArr[i] & bit) == 0)
                {
                    zeros++;
                }
                _pref[l][i + 1] = zeros;
            }

            _zeroBoundary[l] = zeros;

            int leftIdx = 0;
            int rightIdx = zeros;
            for (int i = 0; i < n; i++)
            {
                if ((workingArr[i] & bit) == 0)
                {
                    temp[leftIdx++] = workingArr[i];
                }
                else
                {
                    temp[rightIdx++] = workingArr[i];
                }
            }

            Array.Copy(temp, 0, workingArr, 0, n);
        }
    }

    public int KthSmallestOneIndexed(int from, int exclTo, int k)
    {
        int ans = 0;
        for (int l = _levels - 1; l >= 0; l--)
        {
            int zerosInLeft = _pref[l][from];
            int zerosInRight = _pref[l][exclTo];
            int zerosInInterval = zerosInRight - zerosInLeft;

            if (k <= zerosInInterval)
            {
                from = zerosInLeft;
                exclTo = zerosInRight;
            }
            else
            {
                from = _zeroBoundary[l] + (from - zerosInLeft);
                exclTo = _zeroBoundary[l] + (exclTo - zerosInRight);
                k -= zerosInInterval;
                ans |= (1 << l);
            }
        }

        return ans;
    }

    public int NumEq(int from, int exclTo, int target)
    {
        if (target < 0 || target >= (1 << _levels)) return 0;

        for (int l = _levels - 1; l >= 0; l--)
        {
            int zerosInLeft = _pref[l][from];
            int zerosInRight = _pref[l][exclTo];

            if ((target & (1 << l)) == 0)
            {
                from = zerosInLeft;
                exclTo = zerosInRight;
            }
            else
            {
                from = _zeroBoundary[l] + (from - zerosInLeft);
                exclTo = _zeroBoundary[l] + (exclTo - zerosInRight);
            }

            if (from == exclTo) return 0;
        }

        return exclTo - from;
    }

    public int NumLeq(int from, int exclTo, int target)
    {
        if (target < 0) return 0;
        if (target >= (1 << _levels)) return exclTo - from;

        int count = 0;

        for (int l = _levels - 1; l >= 0; l--)
        {
            int zerosInLeft = _pref[l][from];
            int zerosInRight = _pref[l][exclTo];
            int zerosInInterval = zerosInRight - zerosInLeft;

            if ((target & (1 << l)) == 0)
            {
                from = zerosInLeft;
                exclTo = zerosInRight;
            }
            else
            {
                count += zerosInInterval;
                from = _zeroBoundary[l] + (from - zerosInLeft);
                exclTo = _zeroBoundary[l] + (exclTo - zerosInRight);
            }

            if (from == exclTo) return count;
        }

        count += (exclTo - from);
        return count;
    }

    public int CountInRange(int from, int exclTo, int minVal, int maxVal)
    {
        if (from >= exclTo || minVal > maxVal) return 0;

        int maxLimit = (1 << _levels) - 1;
        if (maxVal > maxLimit) maxVal = maxLimit;
        if (minVal < 0) minVal = 0;
        if (minVal > maxVal) return 0;

        int targetMin = minVal - 1;
        bool trackMin = targetMin >= 0;

        int countMax = 0, countMin = 0;
        int fMax = from, tMax = exclTo;
        int fMin = from, tMin = exclTo;

        for (int l = _levels - 1; l >= 0; l--)
        {
            int[] p = _pref[l];
            int zb = _zeroBoundary[l];
            int bit = 1 << l;

            int zlMax = p[fMax];
            int zrMax = p[tMax];
            if ((maxVal & bit) == 0)
            {
                fMax = zlMax;
                tMax = zrMax;
            }
            else
            {
                countMax += (zrMax - zlMax);
                fMax = zb + fMax - zlMax;
                tMax = zb + tMax - zrMax;
            }

            if (trackMin)
            {
                int zlMin = p[fMin];
                int zrMin = p[tMin];
                if ((targetMin & bit) == 0)
                {
                    fMin = zlMin;
                    tMin = zrMin;
                }
                else
                {
                    countMin += (zrMin - zlMin);
                    fMin = zb + fMin - zlMin;
                    tMin = zb + tMin - zrMin;
                }
            }
        }

        countMax += (tMax - fMax);
        if (trackMin)
        {
            countMin += (tMin - fMin);
        }

        return countMax - countMin;
    }
}
