---
title: "Member Function Template"
date: 2023-06-02 23:01
tags:
- cpp
---
並不限用於 constructor，它常被用來處理賦值操作。

以 `shared_ptr` 為例，它的 copy ctor 可以接受 `weak_ptr` 與 `shared_ptr` (不限此二類，沒有全列)。且包含 copy assignment 也是透過 member function template 達成。

只不過 constructor 類的，除了 generic copy constructor (接收 shared pointer type 的) 是接受隱式轉換的， 

```cpp
template<class T> class shared_ptr {
public:
	// constructor
	template<class Y> // construct from
	explicit shared_ptr(Y * p); // any compatible
	// copy ctor for share_ptr type 
	template<class Y> // built-in pointer,
	shared_ptr(shared_ptr<Y> const& r); // shared_ptr,
	// copy ctor for weak_ptr type 
	template<class Y> // weak_ptr, or
	explicit shared_ptr(weak_ptr<Y> const& r); // auto_ptr
	
	template<class Y> // assign from
	shared_ptr& operator=(shared_ptr<Y> const& r); // any compatible
	
	template<class Y> // shared_ptr or
	shared_ptr& operator=(auto_ptr<Y>& r); // auto_ptr
};
```

## 編譯器依然會自動產生 copying function

條款5中說到，編譯器會自動產生一些 function: [[Default Generated Functions]]
儘管以上透過 member function template 撰寫了 copying function，這不會阻止 compiler 自動生成 那些預設生成的函式!!

試想，當 `T` 和 `U` 相同，呼叫的 funciton 會是 compiler 自動生成的版本? 還是根據模板函式生成一個 `SmartPtr(const SmartPtr<Top>& other)` 的 function? 
```cpp
template<typename T>
class SmartPtr {
public:
	template<typename U> // member template 
	SmartPtr(const SmartPtr<U>& other); // for a ”generalized copy constructor”
}

SmartPtr<Top> pt2 = SmartPtr<Top>(new Top);
```

在 class 內宣告模板函式，並會阻止編譯器生成預設的 copy ctor (non-template)，如果希望完全掌控 copy ctor，則必須**都宣告**
```cpp
template<typename T>
class SmartPtr {
public:
	SmartPtr(SmartPtr const& rhs); // non-template copy ctor

	template<typename U> // template copy ctor
	SmartPtr(const SmartPtr<U>& other); 
}

```