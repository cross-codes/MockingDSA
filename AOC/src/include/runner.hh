#pragma once
#include "defines.hh"

namespace Runner
{
inline void init()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

  const rlim_t stack_size = STACK_SIZE_256M;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size)
  {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }
}
template <typename... FunctionList, size_t... Idxs>
void exec_all_impl(std::index_sequence<Idxs...>, FunctionList &&...fns)
{
  (
      [](int i, auto &&fn) -> void {
        std::cout << "Result #" << i + 1 << ": ";

        FILE *stream = std::freopen("input.txt", "r", stdin);
        if (stream == nullptr)
        {
          std::cerr << "Input file not found\n";
          __builtin_trap();
        }

        std::cin.clear();

        fn();
      }(Idxs, std::forward<FunctionList>(fns)),
      ...);
}

template <typename... FunctionList> void exec_all(FunctionList &&...fns)
{
  exec_all_impl(std::index_sequence_for<FunctionList...>{},
                std::forward<FunctionList>(fns)...);
}

inline void end()
{
  std::cout.flush();
  std::fclose(stdin);
}
} // namespace Runner
