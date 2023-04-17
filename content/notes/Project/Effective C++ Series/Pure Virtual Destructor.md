---
title: "Pure Virtual Destructor"
date: 2023-04-10 22:18
tags:
- cpp
---
現在的情境是，如果，你想要有一個抽象類 -- 抽象類的好處是自身無法被實例化。然而，抽象類的定義是，至少有一個 function 是 Pure Virtural Function。該選擇 "誰" 成為 Pure virtural function 呢? 洽巧手上沒有適合的人選! Destructor 會是個好選擇。因為
1. Abstract Class 總是被當作 Base Class
2. Base Class 作為多型用途時，應當帶有 virtural destructor
3. Pure Virtural Function 可使該 Class 形成 Abstract
三個點串起來--「讓 destructor 變成 Pure Virtural 吧」，這樣不會有不該被 virtural 的 function 遭殃! 

> Abstruct Class 是不能被實例化的 Class，但可以持有 Abstruct Class 的 Pointer 去操控 Child instance。

不過須記得一個技巧 -- 依然為這個 Base Class 的 Destructor 提供一個空的實作。
這是因為 Destructor 的運作規則，在繼承架構中，most derived class (最 child 的) 的 destructor 會最先被呼叫，接著是每一個 Base Class 的 Destructor。即使 `AWOV` 作為抽象類沒有實例化的問題，其 destructor 依然會被呼叫，所以需要提供一個空的實作，Linker (編譯器的一部分?) 會報錯。
```cpp
class AWOV {
public:
	virtural ~AWOV() = 0;
}

AWOV::~AWOV() {}; // 依然為它提供一個實作
```

 