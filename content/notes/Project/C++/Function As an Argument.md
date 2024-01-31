---
title: "Function As an Argument"
date: 2023-05-18 23:47
tags:
- cpp
---

> Array 並不是 C++ 中唯一可以 decay 成 pointer 的東西。function type 也同樣的可以 decay 成 function pointer。

Function Argument 在 Template Type Deduction 的原則跟 Array Argumnet 是一樣的。
```cpp
void func(int double); // function Type: void(int, double)

template <typename T>
void f1(T param);

template <typename T>
void f2(T& param);
```

把 `func` 放入 `f1` 與 `f2` 後，型態推斷如下: 
|  Code   | ParamType  | `T`|
|  ----  | ----  | ---|
| `f1(func)`  | `void (*) (int, double)` |`void (*) (int, double)`|
|  `f2(func)` | `void (&) (int, double)` | `void (int, double)`|
