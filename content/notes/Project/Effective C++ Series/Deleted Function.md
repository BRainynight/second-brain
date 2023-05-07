---
title: "Deleted Function"
date: 2023-05-07 13:27
tags:
- cpp
---


```cpp
class A{    
public:
  A(int x) : m(x) {}
  A& operator = (const A &) = delete;  // Declare the copy assignment operator
                                       // as a deleted function.
  A(const A&) = delete;                // Declare the copy constructor
                                       // as a deleted function.

private:
  int m;
};

int main(){
  A a1(1), a2(2), a3(3);
  a1 = a2;     // Error, the usage of the copy assignment operator is disabled.
  a3 = A(a2);  // Error, the usage of the copy constructor is disabled.
}
```


## 舊的做法
以 C++11 為分水嶺，C++98 只能透過宣告 private 藏住不要 Compiler 生成的 function。
確實 client code 會無法呼叫。但這並不絕對安全，因為 member function 跟 frient function 還是可以呼叫 private function。更安全的做法是，宣告 private 後故意不實作。
