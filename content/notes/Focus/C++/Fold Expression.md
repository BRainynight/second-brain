---
title: Fold Expression
date: 2024-02-29 21:28
tags:
  - cpp
---
> 允許 Progreammer 在「摺疊 (fold)」Parameter Pack 的情況下使用 Binary Operator。

透過 fold expression，一些敘述性的語法 (iterate and sum) 得以被簡化，有點像 Python 的 one line 寫法。 

C++17 可以更簡化，透過 [[Parameter Pack]] 接收任意數量輸入，再透過 fold expression 一行解決 iterate 每個變數並相加。
(C++17 支援 Binary Operator 對 fold argument ? 的運算)
 

 ```cpp
template<class ... Args> // parameter pack
auto sum(Args ... args) { // parameter pack
   return (... + args); // fold expression.
}
```
 
## Reference 
- [Cpp Reference: Fold expressions](https://en.cppreference.com/w/cpp/language/fold)
