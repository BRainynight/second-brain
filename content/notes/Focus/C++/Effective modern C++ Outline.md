---
title: "Effective modern C++ Outline"
date: 2023-05-17 00:04
tags:
- cpp
---
## 外部資源
- [網友中譯版](https://github.com/CnTransGroup/EffectiveModernCppChinese)

## Deducing Types

### 條款1 了解 Template 的型別推斷規則
[[Template ParamType deduction]]

### 條款2 了解 auto 的型別推斷規則


### 條款3 了解 decltype


### 條款4 了解如何檢視型別推斷

## auto
Item 5: Prefer auto to explicit type declarations
Item 6: Use the explicitly typed initializer idiom when auto deduces
undesired types

## Moving to Modern C++
Item 7: Distinguish between () and {} when creating objects: [[Initializer List]]
Item 8: Prefer nullptr to 0 and NULL
### Item 9: Prefer alias declarations to typedefs
[[typedef and using]]

Item 10: Prefer scoped enums to unscoped enums
Item 11: Prefer deleted functions to private undefined ones
Item 12: Declare overriding functions override
## 條款12 對要 override 的 function 以關鍵字 override 明確宣告 
[[override]]
Item 13: Prefer const_iterators to iterators
Item 14: Declare functions noexcept if they won’t emit exceptions
[[Modern C++ noexcept]]

Item 15: Use constexpr whenever possible
[[Item15 constexpr]]
Item 16: Make const member functions thread safe
Item 17: Understand special member function generation

## Smart Pointers
Item 18: Use std::unique_ptr for exclusive-ownership resource management
Item 19: Use std::shared_ptr for shared-ownership resource management
Item 20: Use std::weak_ptr for std::shared_ptr-like pointers that can dangle
Item 21: Prefer std::make_unique and std::make_shared to direct use of new
Item 22: When using the Pimpl Idiom, define special member functions in the implementation file

## Rvalue References, Move Semantics, and Perfect Forwarding
Item 23: Understand std::move and std::forward
Item 24: Distinguish universal references from rvalue references
Item 25: Use std::move on rvalue references, std::forward on universal references
Item 26: Avoid overloading on universal references
Item 27: Familiarize yourself with alternatives to overloading on universal references
Item 28: Understand reference collapsing
Item 29: Assume that move operations are not present, not cheap, and not used
Item 30: Familiarize yourself with perfect forwarding failure cases

## Lambda Expressions
Item 31: Avoid default capture modes
Item 32: Use init capture to move objects into closures
Item 33: Use decltype on auto&& parameters to std::forward them
Item 34: Prefer lambdas to std::bind

## The Concurrency API
Item 35: Prefer task-based programming to thread-based
Item 36: Specify std::launch::async if asynchronicity is essential
Item 37: Make std::threads unjoinable on all paths
Item 38: Be aware of varying thread handle destructor behavior
Item 39: Consider void futures for one-shot event communication
Item 40: Use std::atomic for concurrency, volatile for special memory

## Tweaks
Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied
Item 42: Consider emplacement instead of insertion

## Item1 Template ParamType deduction



## 參考中文
###   推斷型別

項目1：理解模板型別推斷 項目2：理解自動型別推斷 項目3：理解decltype 項目4：了解如何查看推斷的型別

## auto

項目5：優先使用auto而非顯式型別聲明 項目6：在auto推斷出不希望的型別時使用顯式型別初始化惯用法

## 遷移到現代C++

項目7：在創建對象時區分()和{} 
項目8：優先使用nullptr而非0和NULL 
項目9：優先使用別名宣告而非typedef 項目10：優先使用有作用域的枚舉而非無作用域的枚舉 項目11：優先使用已刪除的函數而非私有的未定義函數 項目12：聲明覆蓋的函數使用override 項目13：優先使用const_iterators而非iterators 項目14：如果函數不會引發異常，聲明函數為noexcept 項目15：盡可能使用constexpr 項目16：使const成員函數線程安全 項目17：理解特殊成員函數的生成

## 智能指針

項目18：使用std::unique_ptr進行獨占性資源管理 項目19：使用std::shared_ptr進行共享性資源管理 項目20：使用std::weak_ptr表示可以懸空的std::shared_ptr指針 項目21：優先使用std::make_unique和std::make_shared，而非直接使用new 項目22：在實現文件中定義特殊成員函數時使用Pimpl技法

## Rvalue引用、移動語義和完美轉發

項目23：理解std::move和std::forward 項目24：區分萬能引用和右值引用 項目25：對右值引用使用std::move，對萬能引用使用std::forward 項目26：避免對萬能引用進行重載 項目27：熟悉在萬能引用上進行重載的替代方案 項目28：理解引用折疊 項目29：假設移動操作不存在、不廉價且不被使用 項目30：熟悉完美轉發失敗的情況


### Item5
[[C++11 std function]]


