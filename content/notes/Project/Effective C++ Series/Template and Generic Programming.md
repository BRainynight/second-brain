---
title: "Template and Generic Programming"
date: 2023-06-02 22:05
tags:
- cpp
---

本文中要透過 [[Member Function Template]] (成員函式模板) 完成一個泛化的 copy constructor。

---

這段範例的意思是，對於 `SmartPtr<T>` 存在一個由 `SmartPtr<U>` 建構的管道 (透過 Copy Constructor)。
這邊的型別轉換沒有標示為 `explicit`，一旦標示為 `explicit`，就需要明白寫出轉型 (cast) 動作。
使用隱式轉換式因為 raw pointer 本來就支援隱式轉換，仿效相同模式，`SmartPtr` 也使用隱式轉換。

```cpp
template<typename T>
class SmartPtr {
public:
	template<typename U> // member template 
	SmartPtr(const SmartPtr<U>& other); // for a ”generalized copy constructor”
}
```

現在，不同的 `SmartPtr` 具現體 (instantiations, 具現化的類別) 之間可以自由轉換了，但像是 Top -> Bottom 這種違反繼承規則的不合法的轉換，沒有被禁止! 

我們可以在 copy constructor 中加一些約束條件，避免這種不合法轉換。參考 share pointer 的作法，首先提供一個 `get` 的 public function 讓 raw pointer (`T*`) 得以被取得，這樣在 copy constructor 處理 rhs 的時候，才有辦法取得 `U*` pointer。
接著，在 Member initialization list 當中，把 `U* ptr` 傳給內部的 `T* heldPtr`。若繼承關係不合法，則這個 Raw pointer 之間的 copy 行為就會發生問題，而無法通過編譯!!

```cpp
template<typename T>
class SmartPtr {

public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other) // initialize this held ptr
	: heldPtr(other.get()) { ... } // with other’s held ptr
	T* get() const { return heldPtr; }

private: // built-in pointer held
	T *heldPtr; // by the SmartPtr
};

```