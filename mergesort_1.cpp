#include <rapidcheck.h>

#include <algorithm>


template <typename T>
std::vector<T> merge(std::vector<T> as, std::vector<T> bs) {
  auto a_it = begin(as);
  auto b_it = begin(bs);

  std::vector<T> result;
  result.reserve(as.size() + bs.size());

  while (a_it != end(as) && b_it != end(bs)) {
    auto min = std::min(*a_it, *b_it);

    if (*a_it == min) {
      result.push_back(min);
      ++a_it;
    }
    if (*b_it == min) {
      result.push_back(min);
      ++b_it;
    }
  }

  for (; a_it != end(as); ++ a_it) {
    result.push_back(*a_it);
  }
  for (; b_it != end(bs); ++ b_it) {
    result.push_back(*b_it);
  }

  return result;
}


////////////////////////

int main()
{

  auto unit_test = [](std::vector<int> const& as, std::vector<int> const& bs, std::vector<int> const &expected) {
    if (merge(as, bs) != expected) {
      throw std::runtime_error("unittest failed");
    }
  };

  unit_test({}, {}, {});
  unit_test({1}, {2}, {1, 2});

  unit_test({1, 2, 3}, {4, 5}, {1, 2, 3, 4, 5});
  unit_test({4, 5}, {1, 2, 3}, {1, 2, 3, 4, 5});

  std::cout << "all tests passed\n";


  // demo break
  return 0;


  rc::check(
    "can merge sorted vectors",
    [] (std::vector<int> as, std::vector<int> bs) {

      std::sort(begin(as), end(as));
      std::sort(begin(bs), end(bs));

      auto actual = merge(as, bs);

      std::vector<int> expected;
      expected.insert(end(expected), begin(as), end(as));
      expected.insert(end(expected), begin(bs), end(bs));
      std::sort(begin(expected), end(expected));

      RC_ASSERT( expected == actual);
  });
}
