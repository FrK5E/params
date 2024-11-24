
#include <map>
#include <string>
#include <variant>
#include <optional>

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


template <> void Container::storeParam<A>(const A & arg) { data[Type::A] = arg; };
template <> A Container::getParam<A>() { return std::get<A>(data.at(Type::A)); }

template <> void Container::storeParam<B>(const B &arg) { data[Type::B] = arg; };
template <> B Container::getParam<B>() { return std::get<B>(data.at(Type::B)); };

class ID_A {};
class ID_B {};

enum class Level { 
    LEVEL1, 
    LEVEL2
};

class Settings {

    Settings(){}

    template<class R> 
    std::pair<std::optional<R>,Level>  getParam( const ID_A & id );

    template<class R> 
    std::pair<std::optional<R>,Level>  getParam( const ID_B & id );
};

int main(int argc, char *argv[]) {

  Container c{};

  c.storeParam<B>(B{"HI there"});

  A param = c.getParam<A>();

  return 0;
}