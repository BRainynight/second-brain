---
title: "One Definition Rule"
date: 2023-09-05 21:46
tags:
- cpp
---
>  在一個 translation unit 當中，Symbol 可以被「宣告」無數次，但只能被定義一次。

宣告將符號的**名稱**導入 program 當中，定義提供創建此 symbol 的所有資訊。

如果名稱表示變量，定義會對該變數進行初始化。function definition 包含 signature 與 function body，class definition 包含 class name, class member，然而 member function 的 definition 是允許被放在其他檔案的。

宣告 (Declaration)
```cpp
int i;
int f(int x);
class C;
```
定義 (Definition)
```cpp
int i{42}; // initialize int i
int f(int x){ return x * i; }
class C {
public:
   void DoSomething();
};
```


https://learn.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=msvc-170

> In a C++ program, a _symbol_, for example a variable or function name, can be declared any number of times within its scope. However, it can only be defined once. This rule is the "One Definition Rule" (ODR). 
