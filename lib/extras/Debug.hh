#pragma once
#include <bitset>
#include <concepts>
#include <iostream>
#include <print>
#include <string>
#include <tuple>
#include <vector>

namespace Debug {

template <typename T>
concept Iterable = requires(T a) {
  { std::begin(a) } -> std::input_iterator;
  { std::end(a) } -> std::input_iterator;
} && !std::same_as<T, std::string>;

template <typename A, typename B>
std::string to_string(std::pair<A, B> p);

template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p);

std::string to_string(const std::string &s) { return '"' + s + '"'; }

std::string to_string(const char *s) { return to_string((std::string)s); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

std::string to_string(std::vector<bool> v) {
  bool first      = true;
  std::string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <std::size_t N>
std::string to_string(std::bitset<N> v) {
  std::string res = "";
  for (std::size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <Iterable A>
std::string to_string(A v) {
  bool first      = true;
  std::string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void print() {
#if __cplusplus >= 202302L
  std::print(stderr, "{}", "\n");
#else
  std::cerr << std::endl;
#endif
}

template <typename T, typename... Args>
void print(T H, Args... args) {
#if __cplusplus >= 202302L
  std::print(stderr, " {}", to_string(H));
#else
  std::cerr << " " << to_string(H);
#endif
  print(args...);
}

}  // namespace Debug

#define dbg(...) \
  std::cerr << "[" << #__VA_ARGS__ << "]:", Debug::print(__VA_ARGS__)
