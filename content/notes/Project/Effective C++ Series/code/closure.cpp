//  g++ .\closure.cpp -o main -I "D:\Application\boost_1_82_0"; .\main
// g++ closure.cpp -g -o main -I "/mnt/d/Application/boost_1_82_0"
#include <functional>
#include <string>
#include <iostream>
#include <typeinfo>

#include <boost/core/demangle.hpp>
#include <boost/bind.hpp>
#include<boost/function.hpp>

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

#include <type_traits>
template<class T>
void is_rvalue(T& obj)
{
    bool b = std::is_rvalue_reference<T>() ;
    std::cout<<"rval testing "<< b <<std::endl;
}


template<class T>
void print_ref_type(T&& obj)
{
    if (std::is_rvalue_reference<T>()) {
        std::cout<<"rval"<<std::endl;
    } else if (std::is_lvalue_reference<T>()) {
        std::cout<<"lval"<<std::endl;
    } else if (std::is_reference<T>()) {
        std::cout<<"ref"<<std::endl;
    } else {
        std::cout<<"non"<<std::endl;
    }
}

int main() {
    // auto f1 = boost::bind(Compare2(), 1, 2, false);
    typedef boost::function<bool (int, int)> F;
    
    auto f1 = boost::bind(compare, 1, 2);
    std::cout<<&f1<<std::endl;

    print_ref_type(f1);
    

    const F& f2 = f1;
    std::cout<<"input type is "<<boost::core::demangle( typeid(f1).name() )<<std::endl;
    // foo(f1);


    // clang++ error: candidate function not viable: 
    // no known conversion from '_bi::bind_t<bool, bool (*)(int, int), typename _bi::list_av_2<int, int>::type>' 
    //                             (aka 'bind_t<bool, bool (*)(int, int), list2<value<int>, value<int>>>')                              [input var type]
    // to                       'boost::function<bool (int, int)> &' for 1st argument void foo(boost::function<bool (int, int)>& f)     [func type]
    std::cout<<"input type is "<<boost::core::demangle( typeid(f2).name() )<<std::endl;
    // foo(f2);
    
}
