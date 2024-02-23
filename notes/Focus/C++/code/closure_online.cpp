// https://ideone.com/i58BHo
// error: cannot bind non-const lvalue reference of type ‘boost::function<bool(int, int)>&’  (func type)
//                                      to an rvalue of type ‘boost::function<bool(int, int)>’   (input var type)
// 
#include <functional>
#include<boost/function.hpp>
#include <string>
#include <iostream>
#include <boost/core/demangle.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

//Functor class for comparing 3 integer elements
// using namespace std::placeholders;
class Compare2 {
public:
    // Overloading function call operator which take 3 int argument and return true or false 
    bool operator()(int first, int second, bool Asending) const
    {
        if (Asending)
            return first < second;// Will sort in ascending order
        else
            return first > second; // Will sort in descending order
    }
};

bool compare(int i, int j)
{
  return i > j;
}

void foo(boost::function<bool (int, int)>& f)
{
	std::cout<<"f type is "<<boost::core::demangle( typeid(f).name() )<<std::endl;
}

int main() {
    // auto f1 = boost::bind(Compare2(), 1, 2, false);
    typedef boost::function<bool (int, int)> F;
    auto f1 = boost::bind(compare, 1, 2);
    
    F f2 = f1;
    
    foo(f1); //  error: cannot bind non-const lvalue reference of type ‘boost::function<bool(int, int)>&’ to an rvalue of type ‘boost::function<bool(int, int)>’
    
    foo(f2);
    // auto name = typeid(f1).name();
    // std::cout<<boost::core::demangle( name )<<std::endl;
    // std::cout<<boost::core::demangle( typeid(f2).name() )<<std::endl;
    
}
