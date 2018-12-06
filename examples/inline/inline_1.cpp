#include <execution>
#include <iostream>

namespace execution = std::execution;

class inline_executor
{
public:
  friend bool operator==(const inline_executor&, const inline_executor&) noexcept
  {
    return true;
  }

  friend bool operator!=(const inline_executor&, const inline_executor&) noexcept
  {
    return false;
  }

  template <class Function>
  void execute(Function f) const noexcept
  {
    f();
  }
};

static_assert(execution::is_oneway_executor_v<inline_executor>, "one way executor requirements not met");

int main()
{
  inline_executor ex;
  auto ex2 = std::require_concept(ex, execution::oneway);
  ex2.execute([]{ std::cout << "we made it\n"; });
}
