---
title: "區分介面繼承(interface)和實作繼承(implement)"
date: 2023-04-23 23:15
tags:
- cpp
---

## 背景
Base Class Designer 在設計界面的時候，可能對 Derived Class 實踐者有三種期許
- 只繼承 Member Function Interface (承襲宣告式)
- 同時繼承 Member Function Interface 和**預設的**實作，也可以 override。
- 同時繼承 Member Function Interface 和實作，不允許 override (不要自己改實作!)

## Pure Virtual Function : 只繼承 Interface 需自行實做
[[Pure Virtual Function]] 相當於告訴 Client: 你需要提供一個這樣的函式，但我不干涉你怎麼做它。
```cpp
class Shape {
public:
	virtual void draw() const = 0;
};
```

## Impure Virtual Function : 繼承 Interface 和預設實作
```cpp
class Shape {
public:
	virtual void error(const std::string& msg);
};
```

相當於告訴 Client: 你需要提供一個這樣的函式，如果不想自己寫，可以用預設的內容! 

但是，讓 impure virtual function 同時擔任「要求 client 給一個這樣的函式」又在「實作中放了預設行為」 Client 端可能在不知情下忽略要自己實作，而引發問題 [[Impure Virtual Function]]。

## Non-Virtual Function: 繼承介面與實作，不應重新撰寫實作
代表不變性(invariant)、凌駕特異性(specialization，因此不該在 Derived Class 中重新被定義。
[[絕不重新定義繼承來的 Non-virtual Function]]

## Conclustion
1. 不該將所有的函式宣告成 non-virtual，這會導致 Derived 沒有空間特異化，特別是 non-virtual destructor 會帶來問題: [[為多型用途的基礎類別宣告 virtual 解構式]]
2. 不該將所有的函式宣告成 virtual，某些時候這是正確的，像是 Interface Class。但多數時候這是 Base Class Designer 沒有堅定立場，某些 Function 就是不該在 Base Class 被重新定義! 

