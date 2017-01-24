#include <rapidcheck.h>
#include <rapidcheck/state.h>

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
//      m_data.erase(std::unique(begin(), end()), end());
    }

    void remove(T const& value) {
      auto iter = std::find(m_data.begin(), m_data.end(), value);
      if (iter  != end()) {
        m_data.erase(iter);
      }
    }

    std::size_t size() const {
      return m_data.size();
    }

    typename container::iterator begin() {
      return m_data.begin();
    }

    typename container::const_iterator begin() const {
      return m_data.begin();
    }

    typename container::iterator end() {
      return m_data.end();
    }

    typename container::const_iterator end()  const{
      return m_data.end();
    }

    void print (std::ostream & os) const {
      rc::show(m_data, os);
    }


  private:
    container m_data;
};

template<typename T>
void showValue(flat_set<T> const& value, std::ostream & os) {
  value.print(os);
}



////////////////////////

template<typename T>
struct FlatSetModel {
    std::set<T> model;

    bool operator== (flat_set<T> const& data) const {
      using std::begin;
      using std::end;
      return model.size() == data.size()
          && std::equal(begin(model), end(model), data.begin());
    }
};

template<typename T>
void showValue(FlatSetModel<T> const& model, std::ostream & os) {
  rc::show(model.model, os);
}

template<typename T>
struct InsertOne : rc::state::Command<FlatSetModel<T>, flat_set<T>> {
  T value;

  InsertOne()
    : value(*rc::gen::arbitrary<T>())
  {
  }

  void apply(FlatSetModel<T> &s0) const override {
    s0.model.insert(value);
  }

  void run(const FlatSetModel<T> &s0, flat_set<T> &sut) const override {
    sut.insert(value);
    RC_ASSERT(this->nextState(s0) == sut);
  }

  void show(std::ostream &os) const override {
    os << "InsertOne(" << value << ")";
  }
};


template<typename T>
struct InsertMultiple : rc::state::Command<FlatSetModel<T>, flat_set<T>> {
  std::vector<T> value;

  InsertMultiple()
    : value(*rc::gen::arbitrary<std::vector<T>>())
  {
  }


  void apply(FlatSetModel<T> &s0) const override {
    s0.model.insert(value.begin(), value.end());
  }

  void run(const FlatSetModel<T> &s0, flat_set<T> &sut) const override {
    sut.insert(value.begin(), value.end());
    RC_ASSERT(this->nextState(s0) == sut);
  }

  void show(std::ostream &os) const override {
    os << "InsertMulti(";
    rc::show(value, os);
    os << ")";
  }
};


template<typename T>
struct Remove : rc::state::Command<FlatSetModel<T>, flat_set<T>> {
  T value;

  Remove() : value(*rc::gen::arbitrary<T>())
  {
  }

//  void checkPreconditions(const FlatMapModel<T> &s0) const override {
//    RC_PRE(s0.model.count(value) > 0);
//  }

  void apply(FlatSetModel<T> &s0) const override {
    s0.model.erase(value);
  }

  void run(const FlatSetModel<T> &s0, flat_set<T> &sut) const override {
    sut.remove(value);
    RC_ASSERT(this->nextState(s0) == sut);
  }

  void show(std::ostream &os) const override {
    os << "Remove(" << value << ")";
  }
};



////////////////////////




int main()
{
  using std::begin;
  using std::end;


  rc::check([] {

    FlatSetModel<int> model;
    flat_set<int> sut; // system under test

    rc::state::check(
          model,
          sut,
          &rc::state::gen::execOneOf<InsertOne<int>, InsertMultiple<int>, Remove<int> >
    );
  });
}
