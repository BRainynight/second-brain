---
title: "Template 與隱式介面"
date: 2023-05-24 23:31
tags:
- cpp
---

- 物件導向以顯式介面 (explicit interface) 和執行期多型 (runtime polymorphism) 解決問題。
- Template 與 Generic Programming 而言，隱式介面 (implicit interface) 與編譯期多型 (compile-time) 更重要。

## 多型
|      | 物件導向  | Generic Programming  |
|  ----  | ----  | ----  |
| 多型  | 執行期多型 (runtime polymorphism) | 編譯期多型 (compile-time) |
| 概念(打比方)  | 執行期間決定哪一個 virtual function 要被呼叫 | 編譯期間做 template 具象化、與函式重載決議 (function overloading resolving)| 


## 介面
|      | 物件導向  | Generic Programming  |
|  ----  | ----  | ----  |
| 介面  | 顯式介面 (explicit interface) | 隱式介面 (implicit interface)    |
| 說明  | Signature 由函式名稱、參數型別、反回型態構成，class 明確定義有哪些 function| 沒有定義明確的 signature，只要有對應的 overloading function 被呼叫即可。|

### 顯式介面
- Function Signature 由函式名稱、參數型別、反回型態構成。
	- 對 overloading 而言，函式名稱相同、參數型別相同、return type 不同，無法成功 overload。他們會被視為 duplicate。
	- 但對一個 function 而言，function name, parameter type, return type 是必須的，而 effective C++ 的作者習慣將這三組一起稱為 signature。
- Class 會明確的定義有哪些 function，下例 `Widget` 就有 constructor, destructor, `size`, `normalize`, `swap`。並且 `Widget` 具有 virtual function，表示它有可能有 Derived class 而得以做 runtime polymorphism。

```cpp
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget& other);
};
```

### 隱式介面
再看下例的 Template function: 
```cpp
template<typename T>
void doProcessing(T& w)
{
	if (w.size() > 10 && w != someNastyWidget) { ... }
}
```
乍看下，此 function 對 T 似乎有兩個要求
1. 具有 member function `size`，且回傳一個 int type。
2. 支援 `operator!= `，得以比較 `someNastyWidget` 

實際上 [[operator overloading]] 讓這兩個約束不需要"完全"滿足
- 第一點
	- 確實，T 需要有 `size` 函式，它也可以是從 `T` 的 base class 繼承來的，都可。
	- 但是 return type **不一定** 需要為 int，假設 `T::size` 回傳 type `X`，只要 `(X, int)` 這樣的參數式得以呼喚起一個 `operator>` 即可!
	- 這並非表示要有一個 `operator>(X, int)`，如果 `X` 有能力透過隱式轉換成 `Y`，並且存在 `operator>(Y, int)`，就足以讓此條件滿足了! 
- 第二點
	- 同理，只要有 `operator!=` 支援比較 T 與 type of `someNastyWidget` 就足夠了。
		- 同第一點的邏輯，最低條件需要有一個 `operator!=(X, Y)` 的函式，且 `T` 具有轉換成 `X` 的能力，type of `someNastyWidget` 具有轉換成 `Y` 的能力。

現在，展開 doProcessing 的全貌
```c++
template<typename T>
void doProcessing(T& w)
{
	if (w.size() > 10 && w != someNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}
```

此 template function 同樣對於 member function `normalize`, `swap`, `size`，copy constructor 有要求 -- 總之要讓那些 function 在 `T` 上有效，做甚麼轉換都行!

這些加諸在 `T` 上的「隱晦的要求」，就像是一種隱式介面 -- 能執行成功就代表這個 T 具有這些介面。而被傳入的 `T` 是否具有這些介面，在編譯期間就會檢查。

就像我們無法對顯示介面的 class 呼叫一些不存在的 function 一樣，呼叫了不存在於顯式介面上的函式將無法通過編譯，無法滿足隱式介面的程式也同樣無法通過編譯。


