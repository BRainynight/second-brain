---
title: "Default Generated Functions"
date: 2023-05-07 13:27
tags:
- cpp
---

```cpp
class Empty; // you declare, but implement nothing. 

// Compiler silently create.
class Empty {
public:

    Empty() { ... } // default constructor
    Empty(const Empty& rhs) { ... } // copy constructor
    ~Empty() { ... } // destructor — see below for whether it's virtual
    Empty& operator=(const Empty& rhs) { ... } // copy assignment operator
}

Empty e1;      // default constructor
			   // destructor
Empty e2(e1);  // copy constructor
e2 = e1;       // copy assignment
```


- Default constructor (without parameter) & destructor
	- 給編譯器放一些喚起 base class, non-static member data constructor & destructor 的地方。
	- Compiler 生成的 destructor 是一個 non-virtural
	  [[為多型用途的基礎類別宣告 virtual 解構式]]
	- 只要有宣告 Constructor，編譯器就不會幫我們多掛 default constructor 上去。
- Copy Constructor & Copy Assignment: 將 source 物件的每一個 non-static member data copy 過去。[[Copying Function]]

## Default Copy Assignment
儘管 Copy Assignment `operator=` 也可以自動生成，卻是有條件的自動生成，只有當自動生成的代碼合法時才會生成。

但 default copy assignment 常很有機會變得幾乎無用武之地。
1. 當 User-defined Class 有 member data 是 Reference 或 `const`，自動生成的 code 會不合法。
2. 當 base class 把 copy assignment 宣告成 private，compiler 無法喚起 parent 的 private function，直接裝死。

在 C++ 當中，一旦 Reference 被宣告，是不允許改指向不同物件的，而 Compiler 更不會自動去修改 "被 Reference 物件" 的內容。這種情況，Compiler 會直接拒絕生成 Copy assignment。
如果想讓一個有 reference member data 的 class 有 Copy assignment，需要自行實作。相似的，更改 `const` 成員是不合法的，需自行實作。