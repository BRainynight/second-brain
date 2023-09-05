---
title: "審慎的使用 Private 繼承"
date: 2023-05-07 15:38
tags:
- cpp
- 
---
- Private 繼承代表 implemented in terms of (根據某物實作出)
- 當 `class D` 以 Private 繼承 `class B`，目的是「調用 class B 的 API」，通常意味著只有實作要被繼承，介面不需要。所以 private 繼承來的 function 也只應該放在 private 區塊。
- Private 繼承是實作上的手段，跟 OO design 沒有關係。

## implemented in terms of (根據某物實作出)
在 [[確定 Composition 塑造的是 'Has-A'關係 或 '根據某物實作'的關係]] 裡面也提及 implemented in terms of (根據某物實作出) 的關係。

在多數的情況下，composition 是優於 private 繼承的，只有當
- 要調用 protected member 
- virtual function 需要重新定義
被牽扯進來時才應該考慮 Private 繼承。

即使必須使用 Private 繼承，記住[[讓介面易於被使用，不易誤用]]，我們可以透過一些手段把 Private 繼承的影響「藏起來」
## Private 繼承的範例
情境
1. 有一個 `Widget` 物件，我們想要知道他被呼叫的次數，並且會週期性的檢視它的資料。
2. 為此，需要一個計時器 `Timer`，在工具箱中發現了它! 只要重新定義 `onTick`，在裡面寫取出 Widget 物件的狀態即可!
```c++
class Timer {
public:
	explicit Timer(int tickFrequency);
	virtual void onTick() const; // automatically called for each tick
...
};
```

- Question: 應該讓 Widget 繼承 Timer 嗎?
	- Public 繼承: Widget 並非 Timer，這違反 [[確保 Derived Class 和 Base Class 之間必然保持 Is-a 關係]]
	- Private 繼承: 可以重新定義 `onTick`，客戶端也沒能力呼叫到它，OK。

## Composition + Private 繼承
比起直接的 Private 繼承，我們有更好的做法。
![[Item39.png]]

此作法的好處有兩個
### 為 Base Class 設計做考量
- 如果 Widget 被設計成 Base Class，卻不希望 Derived Class 重新定義 `onTick`，就不適合直接讓 Widget 以 Private 繼承 Timer。但新的設計讓 `WidgetTimer`繼承 Timer 得以重新定義 virtual function，並把 timer 物件放在 private，現在 derived class 想碰也碰不到 timer 了。
```c++
class Widget {
private:
	class WidgetTimer: public Timer {
	public:
		virtual void onTick() const;
		...
	};
 WidgetTimer timer;
...
}
```

### 降低編譯依存性
如果 Widget 繼承 Timer ，則 Widget 被編譯時，Timer 的定義也必須可見。也就是說 Widget 需要 `#include Timer.h`。但如果把 `WidgetTimer` 以一個 pointer 存在 `Widget`，則不再需要 include，達到 decoupling。
[[將檔案的編譯依存關係降到最低]]

```c++
class Widget {
private:
	WidgetTimer* timer; // better way: use smart pointer
}

// In another file
class WidgetTimer: public Timer {
public:
	virtual void onTick() const;
	...
};
```

## 其他
[[EBO (Empty Base Optimization)]]