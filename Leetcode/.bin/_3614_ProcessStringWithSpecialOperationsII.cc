#include <string>

class Solution
{
private:
  class ProcessedString
  {
  public:
    virtual int64_t length()        = 0;
    virtual char char_at(int64_t i) = 0;
  };

  class EmptyString : public ProcessedString
  {
    int64_t length()
    {
      return 0;
    }

    char char_at(int64_t _)
    {
      return 0;
    }
  };

  class AppendedString : public ProcessedString
  {
  private:
    ProcessedString *s;
    char c;
    int64_t len{};

  public:
    AppendedString(ProcessedString *s, char c)
    {
      this->s   = s;
      this->c   = c;
      this->len = s->length() + 1;
    }

    int64_t length()
    {
      return len;
    }

    char char_at(int64_t i)
    {
      if (i == len - 1)
        return c;
      else
        return s->char_at(i);
    }
  };

  class ShortenedString : public ProcessedString
  {
  private:
    ProcessedString *s;
    int64_t len{};

  public:
    ShortenedString(ProcessedString *s)
    {
      this->s = s;
      if (s->length() == 0)
        this->len = 0;
      else
        this->len = s->length() - 1;
    }

    int64_t length()
    {
      return len;
    }

    char char_at(int64_t i)
    {
      return s->char_at(i);
    }
  };

  class DuplicatedString : public ProcessedString
  {
  private:
    ProcessedString *s;
    int64_t len{};

  public:
    DuplicatedString(ProcessedString *s)
    {
      this->s   = s;
      this->len = s->length() << 1;
    }

    int64_t length()
    {
      return len;
    }

    char char_at(int64_t i)
    {
      return s->char_at(i % s->length());
    }
  };

  class ReversedString : public ProcessedString
  {
  private:
    ProcessedString *s;
    int64_t len{};

  public:
    ReversedString(ProcessedString *s)
    {
      this->s   = s;
      this->len = s->length();
    }

    int64_t length()
    {
      return len;
    }

    char char_at(int64_t i)
    {
      return s->char_at(len - i - 1);
    }
  };

public:
  char processStr(std::string s, int64_t k)
  {
    ProcessedString *ps = new EmptyString();
    for (char c : s)
    {
      if (std::islower(c))
        ps = new AppendedString(ps, c);
      else if (c == '*')
        ps = new ShortenedString(ps);
      else if (c == '#')
        ps = new DuplicatedString(ps);
      else
        ps = new ReversedString(ps);
    }

    return k < ps->length() ? ps->char_at(k) : '.';
  }
};
