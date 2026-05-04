using System;
using System.IO;

namespace Evermore.IO;

public class StandardOutputWriter
{
    private const int BUFFER_SIZE = 1048576;
    private readonly byte[] buffer;
    private int pos;
    private readonly Stream stdout;

    public StandardOutputWriter()
    {
        this.pos = 0;
        this.buffer = new byte[BUFFER_SIZE];
        this.stdout = Console.OpenStandardOutput();
    }

    public StandardOutputWriter Append(string s)
    {
        if (s == null) s = "null";
        int length = s.Length;
        this.EnsureCapacity(length);
        for (int i = 0; i < length; i++)
            this.buffer[this.pos++] = (byte)s[i];
        return this;
    }

    public StandardOutputWriter Append(byte[] bytes)
    {
        if (BUFFER_SIZE - this.pos < bytes.Length)
        {
            this.Flush();
            if (bytes.Length > BUFFER_SIZE)
            {
                this.stdout.Write(bytes, 0, bytes.Length);
                return this;
            }
        }
        foreach (byte b in bytes)
            this.buffer[this.pos++] = b;
        return this;
    }

    public StandardOutputWriter Append(byte[] bytes, int from, int to)
    {
        int length = to - from;
        if (BUFFER_SIZE - this.pos < length)
        {
            this.Flush();
            if (length > BUFFER_SIZE)
            {
                this.stdout.Write(bytes, from, length);
                return this;
            }
        }
        for (int i = from; i < to; i++)
            this.buffer[this.pos++] = bytes[i];
        return this;
    }

    public StandardOutputWriter Append(char c)
    {
        this.EnsureCapacity(1);
        this.buffer[this.pos++] = (byte)c;
        return this;
    }

    public StandardOutputWriter Append(int i)
    {
        return this.Append(i.ToString());
    }

    public StandardOutputWriter Append(long l)
    {
        return this.Append(l.ToString());
    }

    public StandardOutputWriter Append(double d)
    {
        return this.Append(d.ToString());
    }

    public StandardOutputWriter AppendAll(params object[] varargs)
    {
        foreach (object obj in varargs)
        {
            this.Append(obj?.ToString() ?? "null");
        }
        return this;
    }

    public void AppendNewLine()
    {
        this.EnsureCapacity(1);
        this.buffer[this.pos++] = (byte)'\n';
    }

    public void Flush()
    {
        if (this.pos > 0)
        {
            this.stdout.Write(this.buffer, 0, this.pos);
            this.pos = 0;
        }
    }

    private void EnsureCapacity(int n)
    {
        if (BUFFER_SIZE - this.pos < n)
            this.Flush();
    }
}
