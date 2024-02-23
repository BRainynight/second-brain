---
title: "少做轉型 Minimize casting"
date: 2023-04-23 23:12
tags:
- cpp
---
## 常見的轉型語法

```cpp
// 舊式轉型
(T) expr; // C-style
T(expr);  // func style

// New-style/ C++ Style  casting 
const_cast<T>(expr);
static_cast<T>(expr);
reinterpret_cast<T>(expr);
dynamic_cast<T>(expr);
```

- `dynamic_cast`: 安全向下轉型 (safe downcasting)，是一個可能耗費重大執行成本的轉型動作
- `static_cast`: 強迫隱式轉換，像是 non-const to const, int to double...，但不能做 const to non-const.
- `const_cast`: 唯一可以做到 const to non-const.

即使舊式轉型依然有用，通常建議用新式，好處是
1. 容易在程式碼中被搜尋
2. 意圖窄化，像是如果想移除 constness，則必須使用 const_cast，其他都不會通過編譯。
```cpp
const int a = 1;
int b = static_cast<int>(a); // fail
int b = const_cast<int>(a); // ok
```


## 不是圖臆測轉型的 Pointer 如何實作

在某些語言中，Drived Class 轉成 Base Class 在 Pointer 上只是一個 Offset。但在 C++ 中，Pointer 是怎麼「算」出來的取決於 Compiler。不要試圖「猜」要抓哪個 Address，相當於 Casting，該用 `static_cast` 就乖乖用。


## 常見的轉型誤用: 試圖使用 Casting 以呼叫 Base Class 方法
有些框架要求 Drived Classes 的 Virtual func 實作時，要先呼叫 Base Class 的對應函式。
在 Python 中，呼叫 Parent 的方法可以使用 `super()`，在 C++ 中，直接在 Drived Class 當中，使用 Base Class 的名稱空間以呼叫 Base Class 方法! 

Example: 
```cpp
class Window {
public:
	virtual void onResize;
}

class SpecicalWindow: public Window {
public: 
	virtual void onResize() {
		// 錯誤作法
		static_cast<Window>(*this).onResize();
		// 正確做法
		Window::onResize();
}
```

錯誤方法的呼叫，相當於
```cpp
Window tmp = static_cast<Window>(*this);
tmp.onResize();
```

## Dynamic Cast

### 效率問題
`dynamic_cast` 有嚴重的效率問題，多重繼承/深度繼承越多，效率成本越大。
某些時候採用它有必要的原因: 需要支援動態連結。

## 如何避免使用?
### Dynamic Cast 的使用場合
手上握有一個 base class pointer/reference，但你認定這個 base class pointer 所指向的對象是某一個 dirved classs。

### Solution1 使用 Type-Safe Container
同樣接續上例的 `Window`

```cpp

std::vector<Window> winPtrs;

typedef std::shared_ptr<SpecialWindow> SPW;
SPW sp_ptr;
sp_ptr = *winPtrs.begin();
```

> [!question] 
> 1. 這裡本質不還是 static cast?
> 2. 如何保證 type 正確?? container 有測試?

### Solution2 在 Base Class 撰寫對應的 Virtual Func
[[區分介面繼承(interface)和實作繼承(implement)]]

```cpp
class Window {
public:
	virtual void onResize;
	virtual void blink() {};
}

class SpecicalWindow: public Window {
public: 
	virtual void onResize() {...};
	virtual void blink() {
		// implement!!
	};
}
```

