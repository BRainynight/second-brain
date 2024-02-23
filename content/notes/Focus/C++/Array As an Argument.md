---
title: "Array As an Argument"
date: 2023-05-18 23:46
tags:
- cpp
---
>- 當 Template 定義成 Pass by value 形式時，傳入的 array name 會轉換成 point to array (the first item)。
> - 當 Template 定義成 Pass by ref 形式時，傳入的 array name 是 **真的傳入整個 Object**。

在進入正文之前須釐清一個觀念，array type 和 pointer type 是不同的，儘管有時候他們「看起來」可以互換。
```cpp
const char name [] = "AAA";   // Type of name is: const char[13]
const char* ptrToName = name; // array decays to pointer
```

`const char[13]` 和 `const char*` 是不同的!! 但是由於有 array-to-pointer decay(退化) rule的規則在，因此上面範例中的 code 是可 compiled 的。

```cpp
template <typename T>
void f(T param);
```

在進入 template deduction 前，先看 array 作為 function parameter 宣告時的兩種形式，這兩種宣告在執行上是等價的。
```cpp
void myFunc(int param[]); // Is treated as a pointer declaration
void myFunc(int* param);  // Like this.
```

Array Parameter 和 Pointer Parameter 之間的等價性源自於 C 語言，並且在 C++ 中保留，這使人誤解 Array Type 和 Pointer Type 是相同的。

根據在 Function Parameter 當中，Array Parameter 被當作 Pointer Parameter 對待，當 Array 被傳入 Template 時會被推斷成 Pointer Type。
```cpp
f(name); // T: const char*
```

但是!! 雖然在 Function Declaration 中，以 Array Parameter 的形式宣告會被以 Pointer 的方式對待，而非以整個 Array 的形式對待，卻可以宣告 **Array Reference** ，就可以傳整個 array 進去。

```cpp
template <typename T>
void f(T& param);

f(name); // pass array to f
		 // T is const char[13]
		 // ParamType is const char(&)[13]
```

有趣的是，不只 `T` 可以被推斷，甚至連 number of elements in array `N` 也可以作為推斷的項目之一。
```cpp
template <typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) no except
{
	return N;
}
```
- About `constexpr`: [[Item15 constexpr]]
- About `noexcept`: [[Modern C++ noexcept]]