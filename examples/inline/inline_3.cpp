#include <experimental/execution>
#include <iostream>

namespace execution = std::experimental::execution;

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
static_assert(execution::is_twoway_executor_v<decltype(execution::require(inline_executor(),
        execution::blocking_adaptation.allowed, execution::twoway))>, "two way executor requirements not met");

int main()
{
  inline_executor ex1;
  auto ex2 = execution::require(ex1, execution::blocking_adaptation.allowed, execution::twoway);
  std::future<int> f = ex2.twoway_execute([]{ return 42; });
  std::cout << "result is " << f.get() << "\n";
}
