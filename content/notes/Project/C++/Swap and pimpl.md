---
title: "Swap and pimpl"
date: 2023-05-07 13:28
tags:
- cpp
---

## std::swap
STL 的 swap 平凡無奇，涉及了三次的複製。
```cpp
namespace std {
    template<typename T>
    void swap (T& a, T& b) {
        T tmp(a);
        a = b;
        b = tmp;
    }
}
```

但對於「某些型別」而言，他們滿足某些資格。因為有這種前提，`std::swap` 的標準做法(三次複製)是多餘的，他們有更快的解法。

「以指標指向一個物件，那個物件含有真正的資料」的型別，就是那些特殊的、滿足資格的傢伙。常見的手法是 [[pimpl idiom (pointer to implementation)]] ，Pattern 如下: 
- `Widget` 的 Copy Assignment 實際上是複製 `rhs.pImpl` 所有內容到自己的 `pImpl` 複製一份過來。
```cpp
class WidgetImpl {
private:
    int a, b, c; 
    ... // a lot of data
}

class Widget {
public:
    Widget(const Widget& rhs);
    // copy assignment: 把 WidgetImpl 的每一個內容都複製一份過來
    Widget& operator=(const Widget& rhs) {
        *pImpl = *(rhs.pImpl); 
    }

private:
    WidgetImpl* pImpl;
}
```

當 Widget 在 swap 時 Copy Assigment 會發生足足三次! 實際上卻是 -- 只要把 `lhs.pImpl` 和 `rhs.pImpl` 兩個 Pointer 互換即可。

## 實作 Swap 
首先，需要用到 [[Template Specialization]] 。我們不被允許改變 STD 空間內的東西，但我們被允許用 STD Template 製造特異化版本，當 swap 用於 `Widget` 物件時自動使用特異化版本的 function。

```cpp
namespace std {
	template<> 
	void swap<Widget> (Widget& a, Widget& b) {
	// 以上兩行表示 total template specialization: 當用在 Widget 時
	// 用這個特異化的 function!
		
		// swap(a.pImpl, b.pImpl); // 會失敗，因為 pImpl 是 private.
		a.swap(b);
	}
}

class Widget {
public:
	void swap(Widget& other) {
		using std::swap; // necessary.
		swap(pImpl, other.pImpl);
	}
}
```

在 `Widget::swap` 裡指定 `using std::swap` 是必要的。

> [!danger]
> 讀到 P111，我懷疑 C++11 之後有不同的做法，先不細看。


## Name Lookup Rules
