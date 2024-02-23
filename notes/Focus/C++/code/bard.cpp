#include <boost/bind.hpp>
#include<boost/function.hpp>
#include <iostream>

class MyObject {
    private:
        int m_x = -1000;
    public:
        void foo() {
            std::cout<<"foo foo"<< -1000 <<std::endl;
        }
};

int main() {
  // Create a temporary MyObject object.
  MyObject* ori = new MyObject();
  MyObject* ptr(ori);
  ptr=nullptr;
  
  MyObject obj;
  
  // boost::bind(&MyObject::foo, obj) is a rvalue.
    boost::function<void()> f1 = boost::bind(&MyObject::foo, obj);
    std::cout<<&f1<<" "<< f1<< std::endl;
    auto f2 = boost::bind(&MyObject::foo, obj);
    std::cout<<"f2 is "<< std::is_rvalue_reference<boost::_bi::bind_t<void, boost::_mfi::mf0<void, MyObject>, boost::_bi::list1<boost::_bi::value<MyObject> > >>();
    // std::cout<<&f2<<" "<<&boost::bind(&MyObject::foo, obj)<< std::endl;


  // This will trigger the Coverity UNINT alarm because the return value of boost::bind is a null pointer.

  std::cout<<"start"<<std::endl;
  f1();
  f2();
  std::cout<<"start"<<std::endl;

    int (*f)(int) = [](int x) { return x * x; };

    // Bind the function object to a specific value of 10.
    boost::function<int(int)> g = boost::bind(f, 10);

    // Try to call the bound function with a value of 20.
    int result = g(20);
    std::cout<<result;


  return 0;
}

/////////
// #include <iostream>
// #include <boost/function.hpp>
// #include <boost/ref.hpp>

// using namespace std;

// bool compare(int i, int j)
// {
//   return i > j;
// }

// int main()
// {
//   // Use a named variable
//   boost::function<bool (int, int)> f1 = boost::bind(compare, 1, 2);

//   cout << f1(10, 20) << endl;

//   // Use boost::ref()
//   boost::function<bool (int, int)> &f2 = boost::ref(boost::bind(compare, 1, 2));

//   cout << f2(10, 20) << endl;

//   return 0;
// }