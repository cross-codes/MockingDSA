#include <algorithm>
#include <array>
#include <charconv>
#include <complex>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <set>
#include <string>
#include <tuple>

namespace BufferedIO {
constexpr auto generate2DLookupArray() -> std::array<std::array<char, 2>, 100> {
  std::array<std::array<char, 2>, 100> res;
  for (uint32_t i = 0; i < 100; ++i) {
    res[i][0] = '0' + (i % 10);
    res[i][1] = '0' + (i / 10);
  }

  return res;
}

class StandardInputReader {
private:
  static constexpr size_t BUF_SIZE = 1 << 16;
  static constexpr size_t NUM_CHARS = 64;
  static constexpr char LAST_WHITESPACE = ' ';

  char mainBuf_[BUF_SIZE];
  char *head_;
  char *tail_;
  std::FILE *input_;

public:
  StandardInputReader() : head_(mainBuf_), tail_(mainBuf_), input_(stdin) {}

  inline auto isStreamEmpty() const -> bool { return head_ == tail_; }

  auto fillBuffer() -> bool {
    long rem = tail_ - head_;
    if (rem > 0) {
      std::memmove(mainBuf_, head_, rem);
    }

    char *readStart = mainBuf_ + rem;
    size_t bytesRead =
        std::fread(readStart, sizeof(char), BUF_SIZE - rem, input_);
    tail_ = readStart + bytesRead;
    head_ = mainBuf_;

    return bytesRead > 0;
  }

  auto skipWhitespace(char last = LAST_WHITESPACE) -> void {
    while (isStreamEmpty() || *head_ <= last) {
      if (isStreamEmpty()) [[unlikely]] {
        fillBuffer();
      } else {
        ++head_;
      }
    }
  }

  template <size_t TOKEN_SIZE = NUM_CHARS>
  auto ensureToken(char last = LAST_WHITESPACE) -> bool {
    bool valid = true;
    static_assert(BUF_SIZE > 2 * TOKEN_SIZE,
                  "Should only need at most one re-read.");
    skipWhitespace(last);

    auto currentSize = static_cast<size_t>(tail_ - head_);
    if (currentSize < TOKEN_SIZE) [[unlikely]] {
      bool didFill = fillBuffer();
      if (!didFill && currentSize == 0) [[unlikely]] {
        return false;
      }

      skipWhitespace(last);
    }

    return valid;
  }

  template <std::integral Num> auto nextInt(Num &num) -> bool {
    if (!ensureToken()) [[unlikely]] {
      return false;
    }

    bool sign = false;
    if constexpr (std::is_signed_v<Num>) {
      if (*head_ == '-') {
        sign = true;
        ++head_;
      }
    }

    constexpr Num BASE{10};
    constexpr char DIGIT_MASK = 0x0f;
    num = *head_ & DIGIT_MASK;
    while (*++head_ > LAST_WHITESPACE) {
      num = BASE * num + (*head_ & DIGIT_MASK);
    }

    if (sign) {
      num = -num;
    }

    return true;
  }

  template <std::floating_point Real> auto nextReal(Real &real) -> bool {
    if (!ensureToken()) [[unlikely]] {
      return false;
    }

#if __cpp_lib_to_chars >= 201611L
    auto [ptr, ec] = std::from_chars(head_, tail_, real);
    head_ = ptr;
#else
    real = static_cast<Real>(std::strtod(head_, &head_));
#endif

    return true;
  }

  auto nextLine(std::string &s, char delim = LAST_WHITESPACE) -> bool {
    skipWhitespace(delim);
    s.clear();

    while (isStreamEmpty() || *head_ > delim) {
      if (isStreamEmpty()) {
        fillBuffer();
      } else {
        s += *head_++;
      }
    }

    return !s.empty();
  }

  template <typename T> auto next(T &var) -> bool {
    *this >> var;
    return true;
  }

  template <typename T, typename... Ts> auto next(T &x, Ts &&...xs) -> bool {
    return next(x) ? next(std::forward<Ts>(xs)...) : false;
  }

  auto next() -> bool { return true; }
};

template <std::integral Num>
auto operator>>(StandardInputReader &in, Num &num) -> StandardInputReader & {
  in.nextInt(num);
  return in;
}

template <std::floating_point Real>
auto operator>>(StandardInputReader &in, Real &real) -> StandardInputReader & {
  in.nextReal(real);
  return in;
}

auto operator>>(StandardInputReader &in, std::string &s)
    -> StandardInputReader & {
  in.nextLine(s);
  return in;
}

template <typename A, typename B>
auto operator>>(StandardInputReader &in, std::pair<A, B> &pair)
    -> StandardInputReader & {
  in.next(pair.first);
  in.next(pair.second);

  return in;
}

template <typename... Ts>
auto operator>>(StandardInputReader &in, std::tuple<Ts...> &tuple)
    -> StandardInputReader & {
  std::apply([&in](Ts &...args) { ((in >> args), ...); }, tuple);
  return in;
}

template <typename C, typename V = decltype(*std::begin(std::declval<C>()))>
auto operator>>(StandardInputReader &in, C &c)
    -> std::enable_if_t<!std::is_same_v<std::remove_cvref<V>, char>,
                        StandardInputReader &> {
  for (auto &v : c) {
    in >> v;
  }

  return in;
}

class StandardOutputWriter {
private:
  static constexpr size_t BUF_SIZE = 1 << 16;
  static constexpr size_t NUM_CHARS = 64;
  static constexpr std::array<std::array<char, 2>, 100> LOOKUP_TWO =
      BufferedIO::generate2DLookupArray();

  char mainBuf_[BUF_SIZE];
  char *tail_;
  std::FILE *output_;
  char delim_;

public:
  StandardOutputWriter() : tail_(mainBuf_), output_(stdout), delim_{' '} {}
  ~StandardOutputWriter() {
    flush();
    std::fflush(output_);
  }

  auto setDelimiter(char delim) -> void { delim_ = delim; }

  auto flush() -> void {
    std::fwrite(mainBuf_, sizeof(char), tail_ - mainBuf_, output_);
    tail_ = mainBuf_;
  }

  auto appendChar(char c) -> void {
    if (tail_ == mainBuf_ + BUF_SIZE) {
      flush();
    }

    *tail_++ = c;
  }

  inline auto appendDelimiter() -> void { appendChar(delim_); }

  template <std::integral Num> auto appendInt(Num num) -> void {
    if constexpr (std::is_signed_v<Num>) {
      if (num < 0) {
        appendChar('-');
        num = -num;
      }
    }

    static std::array<char, 32> buf;
    auto written = 0u;
    while (num >= Num{100}) {
      const auto &digits = LOOKUP_TWO[num % 100];
      buf[written++] = digits[0];
      buf[written++] = digits[1];
      num /= Num{100};
    }
    if (num >= Num{10}) {
      const auto &digits = LOOKUP_TWO[num];
      buf[written++] = digits[0];
      buf[written++] = digits[1];
    } else {
      buf[written++] = static_cast<char>('0' + num);
    }

    std::reverse(buf.begin(), buf.begin() + written);
    if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) [[unlikely]] {
      flush();
    }

    std::memcpy(tail_, buf.begin(), written);
    tail_ += written;
  }

  template <std::floating_point Real> auto appendReal(Real real) -> void {
    if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) [[unlikely]] {
      flush();
    }

    tail_ += std::snprintf(tail_, BUF_SIZE, "%.20lf", real);
  }

  auto appendString(std::string_view sv) -> void {
    for (auto it = sv.begin(); it != sv.end();) {
      if (tail_ == mainBuf_ + BUF_SIZE) {
        flush();
      }

      auto toWrite = std::min(mainBuf_ + BUF_SIZE - tail_, sv.end() - it);
      std::memcpy(tail_, it, toWrite);
      it += toWrite;
      tail_ += toWrite;
    }
  }

  template <typename T, typename... Ts>
  auto appendAll(T &&t, Ts &&...ts) -> void {
    *this << std::forward<T>(t);
    if constexpr (sizeof...(Ts) > 0) {
      appendDelimiter();
      appendAll(std::forward<Ts>(ts)...);
    }
  }

  template <typename... Ts> auto appendAllLn(Ts &&...ts) -> void {
    appendAll(std::forward<Ts>(ts)...);
    appendChar('\n');
  }
};

template <std::integral Num>
auto operator<<(StandardOutputWriter &out, const Num &num)
    -> StandardOutputWriter & {
  out.appendInt(num);
  return out;
}

template <std::floating_point Real>
auto operator<<(StandardOutputWriter &out, const Real &real)
    -> StandardOutputWriter & {
  out.appendReal(real);
  return out;
}

auto operator<<(StandardOutputWriter &out, char c) -> StandardOutputWriter & {
  out.appendChar(c);
  return out;
}

auto operator<<(StandardOutputWriter &out, std::string_view s)
    -> StandardOutputWriter & {
  out.appendString(s);
  return out;
}

template <std::floating_point Real>
auto operator<<(StandardOutputWriter &out, const std::complex<Real> &complex)
    -> StandardOutputWriter & {
  out.appendAll(complex.real, complex.imag);
  return out;
}

template <typename A, typename B>
auto operator<<(StandardOutputWriter &out, const std::pair<A, B> &pair)
    -> StandardOutputWriter & {
  out.appendAll(pair.first, pair.second);
  return out;
}

template <typename C, typename V = decltype(*std::begin(std::declval<C>()))>
auto operator<<(StandardOutputWriter &out, const C &c)
    -> std::enable_if_t<!std::is_same_v<std::remove_cvref_t<V>, char>,
                        StandardOutputWriter &> {
  bool first = true;
  for (const auto &v : c) {
    if (!first) {
      out.appendDelimiter();
    } else {
      first = false;
    }

    out.appendAll(v);
  }

  return out;
}

template <typename... Ts>
auto operator<<(StandardOutputWriter &out, const std::tuple<Ts...> &tuple)
    -> StandardOutputWriter & {
  std::apply([&out](const Ts &...args) { out.appendAll(args...); }, tuple);
  return out;
}
} // namespace BufferedIO