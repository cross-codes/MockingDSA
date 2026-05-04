namespace Evermore.Util;

using System;

public class BarrettReducer
{
    private readonly ulong _mod;
    private readonly ulong _m;

    public BarrettReducer(ulong mod)
    {
        _mod = mod;
        _m = ulong.MaxValue / mod;
    }

    public ulong Reduce(ulong a)
    {
        ulong q = Math.BigMul(_m, a, out _);
        ulong v = unchecked(a - (q * _mod));

        return v >= _mod ? v - _mod : v;
    }
}
