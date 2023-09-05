---
title: "ParamType 非 Reference 或 Pointer"
date: 2023-05-18 23:46
tags:
- cpp
---
當 ParamType 不是 Ref 也非 ptr，真正的 `ParamType=T` 時，傳入的物件會被做 **pass by value**。
在 pass by value 中，只有 pure class infomation 會被保留下來

1. Remove reference-ness
2. Remove constness
3. Remove volatileness (少見)

之所以遵守這個原則是因為，當物件以 Copy (pass by value) 傳進來之後，template function 當中的物件已經跟外面的物件完全脫鉤，對它改變的數值也不該影響到外面 (reference-ness)，而外面的物件能否被改動 (constness) 也不甘 function 內變數的事情。
因此，這些屬性都會被移除。

但是注意下面這個 case:

```cpp
template <typename T>
void f(T param);

const char* const ptr = 'what is this';
f(ptr); // arg type: const char* const
		// T       : const char*
```

ptr 是一個指向 const char 的 pointer (`const char*`)，並且這個 ptr 是不可以被改變的 (`const`)，它必須持續指向被 assigned 的物件。綜合起來就是: ptr 是一個不可被改變的 pointer，它持續指向一個不可被改變的 char 物件。

在它的型態推斷中，由於被 copy 的是 `ptr`，故 ptr 的 constness 會消失。也就是說，ParamType 變成 `const char*`，`parm` 是一個指向「不可被變更的 `char` 物件」的 pointer，但 `parm` **可以更改** 所指的對象，只要對方是一個 `const char` 即可。

> `ptr` 從只喜歡「那一個」短頭髮的女生，變成喜歡短頭髮的女生，哪個都可以。 (渣)

由於被 Copy 的對象是 Pointer，被移除 constness 的也只有 Pointer。Pointer 所指向的對象的 Constness 被保留了下來。
