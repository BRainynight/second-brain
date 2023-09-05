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

## Experiment
實驗以下這份 code，
1. 當 const 與 non-const function 都寫時
```cpp
call non-const func A
call const func B
```
2. 當只寫 const 時
```cpp
call const func A
call const func B
```
3. 當只寫 non-const 時 (宣告 const object, 但不宣告 `const operator[]` )，Compile 的時候就會出問題 
```cpp
Item3.cpp:32:20: error: passing ‘const TextBlock’ as ‘this’ argument discards qualifiers [-fpermissive]
   32 |     std::cout<<t2[0] <<std::endl;
      |                    ^
Item3.cpp:17:15: note:   in call to ‘char& TextBlock::operator[](std::size_t)’
   17 |         char& operator[](std::size_t position)
      |               ^~~~~~~~
```

程式本體:
```cpp
#include <string>
#include <iostream>
// g++ -o main Item3.cpp
class TextBlock
{
public:
    TextBlock(std::string text):m_text(text) { }
	// operator[] for const objects
	const char& operator[](std::size_t position) const
	{ 
        std::cout<<"call const func ";
        return m_text[position]; 
    }
	
	// operator[] for non-const objects
	char& operator[](std::size_t position) 
	{ 
        std::cout<<"call non-const func ";
        return m_text[position]; 
    }

private:
	std::string m_text;
};

int main() {
    TextBlock t1 = TextBlock("AAAA");
    const TextBlock t2 = TextBlock("BBB");
    std::cout<<t1[0] << std::endl; 
    std::cout<<t2[0] <<std::endl;
}
```
