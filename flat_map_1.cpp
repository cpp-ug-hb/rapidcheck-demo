#include <rapidcheck.h>

#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class flat_set
{
  public:
    using container = std::vector<T>;

    void insert(T value) {
      m_data.push_back(std::move(value));
      std::sort(begin(), end());
//      m_data.erase(std::unique(begin(), end()), end());

    }

    template<typename Iter>
    void insert(Iter a, Iter b) {
      m_data.insert(m_data.end(), a, b);
      std::sort(begin(), end());
    }

    void remove(T const& value) {
      m_data.erase(m_data.find(value));
    }

    std::size_t size() const {
      return m_data.size();
    }

    typename container::iterator begin() {
      return m_data.begin();
    }

    typename container::iterator end() {
      return m_data.end();
    }

  private:
    container m_data;
};


int main()
{
  using std::begin;
  using std::end;


  rc::check([] (std::vector<int> data) {

    // fill the flat_map
    flat_set<int> map;
    map.insert(begin(data), end(data));

    // fill a set for comparison
    std::set<int> expected(begin(data), end(data));

    // assert they are equal
    RC_ASSERT(map.size() == expected.size());
    RC_ASSERT(std::equal(begin(map), end(map), begin(expected)));
  });

  return 0;
}
