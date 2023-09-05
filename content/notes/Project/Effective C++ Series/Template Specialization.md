---
title: "Template Specialization"
date: 2023-04-23 11:50
tags:
- cpp
---

Template 可以針對特定的 Type 特化，寫法如下
1. `template<>` 裡面不放任何參數，表示這不是 template 也不是標準的 class，是一個特化的 `MsgSender`。
2. `class MsgSender<CompanyZ>` 表示  template `MsgSender` 在遇到 input type 是 `CompanyZ` 的時候，要用以下定義的內容。
以下這段範例就是 `MsgSender` 針對 `CompanyZ` 特別訂製的內容，這就是模板全特化 (Total Template Specialization)。

```c++
template<> // a total specialization of
class MsgSender<CompanyZ> { // MsgSender; the same as the
public: // general template, except sendClear is omitted
void sendSecret(const MsgInfo& info)
{ ... }
};
```
此例呼應 [[了解如何在 Template 中指涉 Base Class 成員]] 的範例，`MsgSender` 對於一般輸入類別都有 `sendSecret` 跟 `sendClear` 兩個 function。但在這裡，`CompanyZ` 的特化版將不存在 `sendClear`! 

## Template Specialiaztion 與 Declaration
雖然 Template 多習慣把實作寫在 hpp，若將 Template Specialiaztion 實作寫在 hpp 卻可能發生問題。
假設有三個檔案，`temp.hpp` 寫著 template 與 Template Specialiaztion 的實作，兩個 cpp: `a.cpp` 與 `b.cpp` 分別 include  temp.hpp，基於 [[One Definition Rule]]，這會引發 multiple definition (見 [multiple definition of template specialization when using different objects](https://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects))。

解決方法有兩種
1. 宣告 Template Specialiaztion 於 hpp，實作放在 cpp
2. 一樣把實作放在 hpp，但是多宣告 inline 於 Template Specialiaztion 的實作上。

### 分離 Template Specialiaztion 實作

temp.hpp: 
```cpp
template<typename T> void func(T& val);
template<> void func<int>(int& val); // Specialiaztion
```

temp.cpp
```cpp
template<> void func<int>(int& ) {}
```

### 對 Template Specialiaztion 的實作宣告 inline 

這其實相當有趣，因為 function 是否 inline 取決於 compiler，即使宣告 inline 也不一定代表 compiler 會真的對 function inline  ([[了解 Inline 的裡裡外外]])。
那麼為何在 hpp 內對  Template Specialiaztion definition 宣告 inline 能解決問題?  [Stackoverflow 的回答](https://stackoverflow.com/a/48403514) 給出了解答。

根據  C++ standard 條目 3.2:4 ([file](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf) P49 One definition rule)，可以拆成兩段來看: 
> (1) Every program shall contain exactly one definition of every non-inline function or variable that is odr-used in that program; no diagnostic required. The definition can appear explicitly in the program, it can be found in the standard or a user-defined library, or (when appropriate) it is implicitly defined (see 12.1, 12.4 and 12.8). 
> (2) An inline function shall be defined in every translation unit in which it is [[ODR use]].



當 Specialiaztion 不是 inline 的時候，它被當作 non inline function 對待，而對於 non inline function/variable，在 program 中只應該擁有一份 definition。因此兩次 include 同一份 header 造成了問題: 多個 definition (include 的本質就是把 hpp 貼到 cpp 裡面)。

當 Specialiaztion 是 inline 的時候，Specialiaztion 滿足了條目的第二部分: inline function 必須被定義於每一個使用到的 translation unit，也就是該則回答裡面提到的 : 

> an inline function must be defined in each module using the function.

這或許也可以反向說明，在 [[了解 Inline 的裡裡外外]] 環節中提到的，只有 hpp 中含有實作的 function 可以有隱性 inline 申請，因為想要 inline 一個 function，在編譯期間，每一個使用到這個 function 的 translate unit 都需要有這個 function。當實作抽離，這個條件就沒辦法達成。


 There can be more than one definition of a template specialization for which *some template parameters are not specified (14.7, 14.5.5) in a program* provided that each definition appears in a different translation unit

When the parameterized function is not specialized it is covered by clause 3.2:6:

> There can be more than one definition of a class type (Clause 9), enumeration type (7.2), inline function with external linkage (7.1.2), class template (Clause 14), non-static function template (14.5.6), static data member of a class template (14.5.1.3), member function of a class template (14.5.1.1), or template specialization for which some template parameters are not specified (14.7, 14.5.5) in a program provided that each definition appears in a different translation unit

This clause states that it is OK for multiple definitions of the same template function as long as at least one of the template parameters is not specified in the code. This is to allow the decision on whether the parameterized function should be instantiated in a module to be made on local information only.

[Example ORD](https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL60-CPP.+Obey+the+one-definition+rule)
https://en.cppreference.com/w/cpp/language/definition