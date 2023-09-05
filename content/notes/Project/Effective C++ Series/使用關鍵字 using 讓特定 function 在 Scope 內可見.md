---
title: "使用關鍵字 using 讓特定 function 在 Scope 內可見"
date: 2023-05-09 00:36
tags:
- cpp
---
首先了解 [[繼承時的名稱遮掩行為]]。

如果，我們只是想為 Derived Class 增加同名稱、Signature 不同的 function? 我們希望 Base Class 的 function 仍然可以被使用! 則，需要做的是用 `using` 讓 Base Function 變得可見，如下例: 

```cpp
class Derived: public Base {
public:
	using Base::mf1; // make all things in Base named mf1 and mf3
	using Base::mf3; // visible (and public) in Derived’s scope
	virtual void mf1();
	void mf3(); // override Derived::mf3, even 
	void mf4();
...
};

Derived d;
int x;
...
d.mf1(); // still fine, still calls Derived::mf1
d.mf1(x); // now okay, calls Base::mf1
d.mf2(); // still fine, still calls Base::mf2
d.mf3(); // fine, calls Derived::mf3
d.mf3(x); // now okay, calls Base::mf3 
// (The int x is implicitly converted to a double so that  the call to Base::mf3 is valid.)
```

`using` 放在 public 是因為 Public 繼承，function 在 Base class 是 public ，基於正確的 public 繼承前提，Derived Class 在 `using` 暴露 Base Class 的 function name 時，也應該要是 Public 。

- 可以不要繼承所有 Base Class 的所有函式嗎?
	- 在 Public 繼承下這不可能發生，這違反了 [[確保 Derived Class 和 Base Class 之間必然保持 Is-a 關係]]。

## Private 繼承: 使用 forwarding function 繼承部分函式
不繼承所有 Base Class 的所有函式，在 Private 繼承是有意義的。同樣的遇到名稱遮掩問題，該怎麼做?

同樣以下圖為例，如果 Derived Class 只要 `void mf3()`，不要 `void mf3(double)`? 
![[Itm33.png]]

那將無法使用 `using`，因為用下去所有的 `Base::mf3` 都會變得可見。這時候要換個手法: forwarding function。

```cpp
class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	... // as before
};
class Derived: private Base {
public:
	virtual void mf1() { Base::mf1(); } 
	// forwarding function; implicitly inline — see Item 30. 
	// (For info on calling a pure virtual function, see Item 34.)
}; 

Derived d;
int x;
d.mf1(); // fine, calls Derived::mf1
d.mf1(x); // error! Base::mf1() is hidden
```


當繼承結合 Template，繼承名稱遭到遮掩的問題會再度發生，參見 [[了解如何在 Template 中指涉 Base Class 成員]]