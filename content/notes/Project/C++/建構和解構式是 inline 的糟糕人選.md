---
title: "建構和解構式是 inline 的糟糕人選"
date: 2023-05-07 12:35
tags:
- cpp
---

考量以下例子:
```cpp
class Base {
public:
...
private:
	std::string bm1, bm2; // base members 1 and 2
};
class Derived: public Base {
public:
	Derived() {} // Derived’s ctor is empty — or is it?
...
private:
	std::string dm1, dm2, dm3; // derived members 1–3
};
```
建構式 `Derived::Derived` 乍看內容是「空的」很適合 inlining?

別忘了，物件產生的時候，每一個 Base Class、每一個成員變數的 constructor 都會被呼叫，反之，物件被銷毀時，destructor 也會依序呼叫。

這些動作並非憑空發生，Compiler 在編譯期間會代為產生，並安插到程式碼中，彷彿以下內容就是 Compiler 代為成生的 (這並非實際會生成的，編譯器會更精巧的處理 exception)。

```cpp
Derived::Derived() // conceptual implementation of
{ // “empty” Derived ctor
	Base::Base(); // initialize Base part
	try { dm1.std::string::string(); } // try to construct dm1
	catch (...) { // if it throws,
	Base::~Base(); // destroy base class part and
	throw; // propagate the exception
}
try { dm2.std::string::string(); } // try to construct dm2
catch(...) { // if it throws,
	dm1.std::string::~string(); // destroy dm1,
	Base::~Base(); // destroy base class part, and
	throw; // propagate the exception
}
try { dm3.std::string::string(); } // construct dm3
catch(...) { // if it throws,
	dm2.std::string::~string(); // destroy dm2,
	dm1.std::string::~string(); // destroy dm1, 
	Base::~Base(); // destroy base class part, and
	throw; // propagate the exception
}
}
```

但從本例我們可以看到，`Derived::Derived` 會去呼叫 `Base::Base` ，如果試圖對 `Derived::Derived` 做 `inline`，Compiler 會檢視 `Derived::Derived` 所呼叫的 funciton，決定 `Derived::Derived` 是否有被 `inline` 的資格。

如果每一個在 `Derived::Derived` 當中被呼叫的都是 inlined function .... 讓我們一一檢視這件事

- 假設 std::string constructor 是 inline function。
- `Base::Base` 被宣告 inline ，它要呼叫 `bm1`, `bm2` 兩次 std::string constructor。
- `Derived::Derived`: 被宣告 inline ，光是自己的 member data (不含 base) 要呼叫 `dm1`, `dm2`, `dm3` 三次 std::string constructor。

`Derived::Derived` 總共要呼叫 5次 std::string constructor，一旦宣告成 inline，std::string constructor code 會插入**5份**在 `Derived::Derived` !!



