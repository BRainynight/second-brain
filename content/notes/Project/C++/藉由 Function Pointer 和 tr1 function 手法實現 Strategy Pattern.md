---
title: "藉由 Function Pointer 手法實現 Strategy Pattern"
date: 2023-05-14 15:18
tags:
- cpp
---

NVI 方法為 Public Virtual Function 提供了替代方案，但仍沒有脫離 virtual。
新的做法是，把 Function 用 Function Pointer 傳入，這實際上是  [[Classic Strategy Pattern|Strategy Pattern]] 的一種實作。

```cpp
class GameCharacter; // forward declaration
// function for the default health calculation algorithm
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter {
public:
	typedef int (*HealthCalcFunc)(const GameCharacter&);

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
	: healthFunc(hcf) {}
	
	int healthValue() const { return healthFunc(*this); }

private:
	HealthCalcFunc healthFunc;
}
```

更進一步的，使用 `tr1::function`，使得任何像是 function 一般 callable 且 signature 符合的 callable 物件 (`std::tr1::function<int (const GameCharacter&)>`)，都可以是被傳入的物件。
[[C++11 std function]]

```cpp
class GameCharacter; // as before
int defaultHealthCalc(const GameCharacter& gc); // as before
class GameCharacter {
public:
// HealthCalcFunc is any callable entity that can be called with
// anything compatible with a GameCharacter and that returns anything
// compatible with an int; see below for details
typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;
explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
: healthFunc(hcf )
{}
int healthValue() const 
{ return healthFunc(*this); }
...
private:
HealthCalcFunc healthFunc;
}
```

## 優點
- 可以在 RT 期間決定傳入的函式

## 缺點
當我們想計算的內容都可以用 Public Interface 取得相關資訊，沒有問題。但如果需要取得 non-public data (內部資訊)，就有疑慮了。
- 讓 class 的某個**內部**機能依賴於外部的某個 [[non-member && non-friend function]] 是個爭議。
- 解決作法是弱化 class 的封裝，宣告該 function 為 friend function 就是一種弱化的作法，或是提供一個 public getter。

