
#include <boost/serialization/strong_typedef.hpp>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <variant>

class A {};
class B {
public:
  std::string name;
};

class Container {
public:
  template <class R> R getParam();

  template <class R> void storeParam(const R &arg);

  template <class R> bool hasParam();

private:
  using MyDataType = std::variant<A, B>;
  enum class Type { A, B };
  std::map<Type, MyDataType> data;
};

template <> void Container::storeParam<A>(const A &arg) {
  data[Type::A] = arg;
};
template <> A Container::getParam<A>() { return std::get<A>(data.at(Type::A)); }

template <> void Container::storeParam<B>(const B &arg) {
  data[Type::B] = arg;
};
template <> B Container::getParam<B>() {
  return std::get<B>(data.at(Type::B));
};

BOOST_STRONG_TYPEDEF(int, ID_A);
BOOST_STRONG_TYPEDEF(int, ID_B);

enum class LevelId { LEVEL1, LEVEL2 };

class Settings {
public:
  Settings() {
    level_A_members[ID_A{1}];
    level_B_members[ID_B{1}];
    level_A_members[ID_A{1}].storeParam(B{"Hello world"});
  };

  template <class R>
  std::pair<std::optional<R>, LevelId> getParam(const ID_A &id) {
    if (level_A_members.contains(id)) {
      return {level_A_members[id].getParam<R>(), LevelId::LEVEL1};
    }
    return {{}, LevelId::LEVEL1};
  };

  template <class R>
  std::pair<std::optional<R>, LevelId> getParam(const ID_B &id) { 
    if ( level_B_members.contains(id)) { 
        return {level_B_members[id].getParam<R>(), LevelId::LEVEL2};
    }
    return {{}, LevelId::LEVEL2};
  }

private:
  std::map<ID_A, Container> level_A_members;
  std::map<ID_B, Container> level_B_members;
};

int main(int argc, char *argv[]) {

  Settings s{};

  auto value = s.getParam<B>(ID_A{1});

  std::cout << value.first.value().name << std::endl;

  return 0;
}