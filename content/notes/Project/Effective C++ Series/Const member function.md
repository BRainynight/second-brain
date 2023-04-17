---
title: "Const member function"
date: 2023-04-10
tags:
- cpp
---

> The purpose of const on member functions is to identify which member functions may be invoked on const object.

使 Interface 意圖更加清楚，有兩個重要的優點
1. 可知道哪個 function 會更動到物件
2. 改善 C++ 程式效率與 "pass by reference to const" 息息相關，使 function 可操作 Const Object 。

直接看例子: 我們定義了如下的 Interface。

```cpp
class TextBlock
{
public:
	// operator[] for const objects
	const char& operator[](std::size_t position) const
	{ return text[position]; }
	
	// operator[] for non-const objects
	char& operator[](std::size_t position) 
	{ return text[position]; }
private:
	std::string text;
};
```

在 Client 端，`const TextBlock` 與 `TextBlock` 物件會 call 到的  `TextBlock::operator[]` **是不同的**!! 有宣告 Interface 的第一條 (const function)，才有辦法操作 `const TextBlock` 的物件。
```cpp
const TextBlock ctb("World");
std::cout << ctb[0]; // calls const TextBlock::operator[]

TextBlock tb("Hello");
std::cout << tb[0]; // calls non-const TextBlock::operator[]
```


> [!question] 
> 如果宣告 Const 但是不定義 const TextBlock 會怎樣?
