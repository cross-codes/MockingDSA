#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

// clang-format off

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/crt-disable-perfcrit-locks
#ifdef _WIN32
  #define _CRT_DISABLE_PERFCRIT_LOCKS
#endif

#ifndef __INTEL_LLVM_COMPILER
  #pragma GCC optimize("Ofast,unroll-loops")
  #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

// clang-format on

// https://github.com/cross-codes/MockingDSA/blob/master/lib/extras/IO.hpp
struct IOPreProc {

  static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;

  std::array<char, 4 * SZ> num;
  constexpr IOPreProc() : num{} {
    for (int i = 0; i < SZ; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i * 4 + j] = static_cast<char>(n % TEN + '0');
        n /= TEN;
      }
    }
  }
};

struct IO {
// https://stackoverflow.com/questions/48291991
#ifndef HAVE_DECL_FREAD_UNLOCKED
  #define fread_unlocked fread
#endif
#ifndef HAVE_DECL_FWRITE_UNLOCKED
  #define fwrite_unlocked fwrite
#endif
  static constexpr int SZ = 1 << 17, LEN = 32, TEN = 10, HUNDRED = TEN * TEN,
                       THOUSAND = HUNDRED * TEN, TENTHOUSAND = THOUSAND * TEN,
                       MAGIC_MULTIPLY = 205, MAGIC_SHIFT = 11, MASK = 15,
                       TWELVE = 12, SIXTEEN = 16;

  static constexpr IOPreProc io_pre = {};
  std::array<char, SZ> input_buffer, output_buffer;
  int input_ptr_left, input_ptr_right, output_ptr_right;

  IO()
      : input_buffer{}, output_buffer{}, input_ptr_left{}, input_ptr_right{},
        output_ptr_right{} {}
  IO(const IO &) = delete;
  IO(IO &&) = delete;
  IO &operator=(const IO &) = delete;
  IO &operator=(IO &&) = delete;

  ~IO() { flush(); }

  template <class T> struct is_char {
    static constexpr bool value = std::is_same_v<T, char>;
  };

  template <class T> struct is_bool {
    static constexpr bool value = std::is_same_v<T, bool>;
  };

  template <class T> struct is_string {
    static constexpr bool value =
        std::is_same_v<T, std::string> || std::is_same_v<T, const char *> ||
        std::is_same_v<T, char *> || std::is_same_v<std::decay_t<T>, char *>;
    ;
  };

  template <class T, class D = void> struct is_custom {
    static constexpr bool value = false;
  };

  template <class T>
  struct is_custom<T, std::void_t<typename T::internal_value_type>> {
    static constexpr bool value = true;
  };

  template <class T> struct is_default {
    static constexpr bool value = is_char<T>::value || is_bool<T>::value ||
                                  is_string<T>::value || std::is_integral_v<T>;
  };

  template <class T, class D = void> struct is_iterable {
    static constexpr bool value = false;
  };

  template <class T>
  struct is_iterable<
      T, typename std::void_t<decltype(std::begin(std::declval<T>()))>> {
    static constexpr bool value = true;
  };

  template <class T, class D = void, class E = void> struct is_applyable {
    static constexpr bool value = false;
  };

  template <class T>
  struct is_applyable<T, std::void_t<typename std::tuple_size<T>::type>,
                      std::void_t<decltype(std::get<0>(std::declval<T>()))>> {
    static constexpr bool value = true;
  };

  template <class T>
  static constexpr bool needs_newline =
      (is_iterable<T>::value || is_applyable<T>::value) &&
      (!is_default<T>::value);
  template <typename T, typename U> struct any_needs_newline {
    static constexpr bool value = false;
  };

  template <typename T> struct any_needs_newline<T, std::index_sequence<>> {
    static constexpr bool value = false;
  };

  template <typename T, std::size_t I, std::size_t... Is>
  struct any_needs_newline<T, std::index_sequence<I, Is...>> {
    static constexpr bool value =
        needs_newline<decltype(std::get<I>(std::declval<T>()))> ||
        any_needs_newline<T, std::index_sequence<Is...>>::value;
  };

  inline void load() {
    memmove(std::begin(input_buffer), std::begin(input_buffer) + input_ptr_left,
            input_ptr_right - input_ptr_left);
    input_ptr_right =
        input_ptr_right - input_ptr_left +
        static_cast<int>(fread_unlocked(
            std::begin(input_buffer) + input_ptr_right - input_ptr_left, 1,
            SZ - input_ptr_right + input_ptr_left, stdin));
    input_ptr_left = 0;
  }

  inline void read_char(char &c) {
    if (input_ptr_left + LEN > input_ptr_right)
      load();
    c = input_buffer[input_ptr_left++];
  }

  inline void read_string(std::string &x) {
    char c;
    while (read_char(c), c < ' ')
      continue;
    x = c;
    while (read_char(c), c >= ' ')
      x += c;
  }

  template <class T>
  inline std::enable_if_t<std::is_integral_v<T>, void> read_int(T &x) {
    if (input_ptr_left + LEN > input_ptr_right)
      load();
    char c = 0;
    do
      c = input_buffer[input_ptr_left++];
    while (c < '-');
    [[maybe_unused]] bool minus = false;
    if constexpr (std::is_signed<T>::value == true)
      if (c == '-')
        minus = true, c = input_buffer[input_ptr_left++];
    x = 0;
    while (c >= '0')
      x = x * TEN + (c & MASK), c = input_buffer[input_ptr_left++];
    if constexpr (std::is_signed<T>::value == true)
      if (minus)
        x = -x;
  }

  inline void skip_space() {
    if (input_ptr_left + LEN > input_ptr_right)
      load();
    while (input_buffer[input_ptr_left] <= ' ')
      input_ptr_left++;
  }

  inline void flush() {
    fwrite_unlocked(std::begin(output_buffer), 1, output_ptr_right, stdout);
    output_ptr_right = 0;
  }

  inline void write_char(char c) {
    if (output_ptr_right > SZ - LEN)
      flush();
    output_buffer[output_ptr_right++] = c;
  }

  inline void write_bool(bool b) {
    if (output_ptr_right > SZ - LEN)
      flush();
    output_buffer[output_ptr_right++] = b ? '1' : '0';
  }

  inline void write_string(const std::string &s) {
    for (auto x : s)
      write_char(x);
  }

  inline void write_string(const char *s) {
    while (*s)
      write_char(*s++);
  }

  inline void write_string(char *s) {
    while (*s)
      write_char(*s++);
  }

  template <typename T>
  inline std::enable_if_t<std::is_integral_v<T>, void> write_int(T x) {
    if (output_ptr_right > SZ - LEN)
      flush();
    if (!x) {
      output_buffer[output_ptr_right++] = '0';
      return;
    }
    if constexpr (std::is_signed<T>::value == true)
      if (x < 0)
        output_buffer[output_ptr_right++] = '-', x = -x;
    int i = TWELVE;
    std::array<char, SIXTEEN> buf{};
    while (x >= TENTHOUSAND) {
      memcpy(std::begin(buf) + i,
             std::begin(io_pre.num) + (x % TENTHOUSAND) * 4, 4);
      x /= TENTHOUSAND;
      i -= 4;
    }
    if (x < HUNDRED) {
      if (x < TEN) {
        output_buffer[output_ptr_right++] = static_cast<char>('0' + x);
      } else {
        std::uint32_t q =
            (static_cast<std::uint32_t>(x) * MAGIC_MULTIPLY) >> MAGIC_SHIFT;
        std::uint32_t r = static_cast<std::uint32_t>(x) - q * TEN;
        output_buffer[output_ptr_right] = static_cast<char>('0' + q);
        output_buffer[output_ptr_right + 1] = static_cast<char>('0' + r);
        output_ptr_right += 2;
      }
    } else {
      if (x < THOUSAND) {
        memcpy(std::begin(output_buffer) + output_ptr_right,
               std::begin(io_pre.num) + (x << 2) + 1, 3),
            output_ptr_right += 3;
      } else {
        memcpy(std::begin(output_buffer) + output_ptr_right,
               std::begin(io_pre.num) + (x << 2), 4),
            output_ptr_right += 4;
      }
    }
    memcpy(std::begin(output_buffer) + output_ptr_right,
           std::begin(buf) + i + 4, TWELVE - i);
    output_ptr_right += TWELVE - i;
  }

  template <typename T_> IO &operator<<(T_ &&x) {
    using T =
        typename std::remove_cv<typename std::remove_reference<T_>::type>::type;
    static_assert(is_custom<T>::value or is_default<T>::value or
                  is_iterable<T>::value or is_applyable<T>::value);
    if constexpr (is_custom<T>::value) {
      write_int(x.get());
    } else if constexpr (is_default<T>::value) {
      if constexpr (is_bool<T>::value) {
        write_bool(x);
      } else if constexpr (is_string<T>::value) {
        write_string(x);
      } else if constexpr (is_char<T>::value) {
        write_char(x);
      } else if constexpr (std::is_integral_v<T>) {
        write_int(x);
      }
    } else if constexpr (is_iterable<T>::value) {
      using E = decltype(*std::begin(x));
      constexpr char sep = needs_newline<E> ? '\n' : ' ';
      int i = 0;
      for (const auto &y : x) {
        if (i++)
          write_char(sep);
        operator<<(y);
      }
    } else if constexpr (is_applyable<T>::value) {
      constexpr char sep =
          (any_needs_newline<
              T, std::make_index_sequence<std::tuple_size_v<T>>>::value)
              ? '\n'
              : ' ';
      int i = 0;
      std::apply(
          [this, &sep, &i](auto const &...y) {
            (((i++ ? write_char(sep) : void()), this->operator<<(y)), ...);
          },
          x);
    }
    return *this;
  }

  template <typename T> IO &operator>>(T &x) {
    static_assert(is_custom<T>::value or is_default<T>::value or
                  is_iterable<T>::value or is_applyable<T>::value);
    static_assert(!is_bool<T>::value);
    if constexpr (is_custom<T>::value) {
      typename T::internal_value_type y;
      read_int(y);
      x = y;
    } else if constexpr (is_default<T>::value) {
      if constexpr (is_string<T>::value) {
        read_string(x);
      } else if constexpr (is_char<T>::value) {
        read_char(x);
      } else if constexpr (std::is_integral_v<T>) {
        read_int(x);
      }
    } else if constexpr (is_iterable<T>::value) {
      for (auto &y : x)
        operator>>(y);
    } else if constexpr (is_applyable<T>::value) {
      std::apply([this](auto &...y) { ((this->operator>>(y)), ...); }, x);
    }
    return *this;
  }

  IO *tie(std::nullptr_t) { return this; }
  void sync_with_stdio(bool) {}
} io;

#define cin ::io
#define cout ::io

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

// https://github.com/cross-codes/MockingDSA/blob/master/lib/util/Array.hpp
class Array {
private:
  Array();

  template <typename T, typename Procedure>
    requires std::integral<T> || std::floating_point<T>
  static void permute(std::vector<T> &vector, int length,
                                Procedure &&procedure) {
    if (length == 1)
      std::invoke(std::forward<Procedure>(procedure));
    else {
      permute(vector, --length, std::forward<Procedure>(procedure));
      for (int i = 0; i < length; i++) {
        int index = (length & 1) == 0 ? 0 : i;
        std::swap(vector[index], vector[length]);
        permute(vector, length, std::forward<Procedure>(procedure));
      }
    }
  }

public:
  inline static void sort(std::vector<int> &vector) {
    int bits = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix,
                                          std::vector<int>(vector.size()));
    std::vector<int> size(radix);
    for (int e : vector) {
      int index = e & radix - 1;
      buckets[index][size[index]++] = e;
    }
    std::vector<std::vector<int>> newBuckets(radix,
                                             std::vector<int>(vector.size()));
    for (int i = bits; i < sizeof(int) * 8; i += bits) {
      std::vector<int> newSize(radix);
      for (int j = 0; j < radix; j++) {
        for (int k = 0; k < size[j]; k++) {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          newBuckets[index][newSize[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, newBuckets);
      size = newSize;
    }
    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++) {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++) {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
    }
  }

  template <typename T, typename Procedure>
    requires std::integral<T> || std::floating_point<T>
  static void permute(std::vector<T> vector,
                                Procedure &&procedure) {
    permute(vector, vector.size(), std::forward<Procedure>(procedure));
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline static int __jdk__binarySearch(std::vector<T> const &vec,
                                           int fromIndex, int toIndex, T key) {
    int low = fromIndex;
    int high = toIndex - 1;
    while (low <= high) {
      int mid = (low + high) >> 1;
      if (vec[mid] < key)
        low = mid + 1;
      else if (vec[mid] > key)
        high = mid - 1;
      else
        return mid;
    }

    return -(low + 1);
  }
};

int main() {
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    i64 x, y;
    cin >> x >> y;

    i64 sum = 0LL;
    std::vector<i64> nums(n);
    for (int i = 0; i < n; i++) {
      i64 num;
      cin >> num;
      nums[i] = num;
      sum += num;
    }

    std::sort(nums.begin(), nums.end());

    i64 numberOfPairs = 0LL;
    for (int i = 0; i < n; i++) {
      i64 currDiff = sum - nums[i];
      i64 lowerBound = currDiff - y, upperBound = currDiff - x;

      int lowerIndex =
          Array::__jdk__binarySearch<i64>(nums, i + 1, n, lowerBound);
      if (lowerIndex < 0) {
        lowerIndex = -(lowerIndex + 1);
      }
      if (lowerIndex == n)
        continue;

      i64 refVal = nums[lowerIndex];

      for (int j = lowerIndex - 1; j > i; j--) {
        if (nums[j] == refVal)
          lowerIndex--;
        else
          break;
      }

      int upperIndex =
          Array::__jdk__binarySearch<i64>(nums, i + 1, n, upperBound);
      if (upperIndex < 0) {
        upperIndex = -(upperIndex + 1) - 1;
        if (upperIndex + 1 == lowerIndex)
          continue;
      }

      refVal = nums[upperIndex];

      for (int j = upperIndex + 1; j < n; j++) {
        if (nums[j] == refVal)
          upperIndex++;
        else
          break;
      }

      numberOfPairs += upperIndex - lowerIndex + 1;
    }

    cout << numberOfPairs << "\n";
  }
}
