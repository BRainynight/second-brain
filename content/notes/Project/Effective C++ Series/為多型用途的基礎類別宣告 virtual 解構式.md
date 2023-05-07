---
title: "為多型用途的基礎類別宣告 virtual 解構式"
date: 2023-05-07 13:27
tags:
- cpp
---

## 多型
多型有個特點: Base Class 的存在是為了「經由 Base Class Interface 處置 Drived Class Object」，以下例來說， `TimeKeeper` 是一個 Polymorphic Base Class，所以持有一個 `TimeKeeper` Pointer 就可以處理 `WaterClock`, `WristWatch` 物件，這就是上面那句話的意思。

```cpp
class TimeKeeper {
public:
	TimeKeeper();
	virtural ~TimeKeeper();
};
class AtomicClock: public TimeKeeper { ... };
class WaterClock: public TimeKeeper { ... };
class WristWatch: public TimeKeeper { ... };

TimeKeeper* getTimeKeeper(); 
// Returned pointer may be AtomicClock, WaterClock, WristWatch
// But they can be owned by base class "TimeKeeper"
// This is polymorphy.
```

繼承與多型之間並非充分必要條件，**非所有的 Base Class 都是作為多型使用**。
像是 [[Item47 Use traits classes for information about types]] 的 `input_iterator_tag`，繼承更像是 "enable 某種特性" 的用途。 


## 多型的 Base Class 沒有 Virtural Destructor 又如何
多型 (polymorphic) 的手法使我們可以持有 base class 的 Pointer 指向各種 child class 的實作。[[工廠函式 (Factory Function)]]  就是典型的實作。

> [!question]
> 為了遵守 factory function 的規矩，哪來的規矩?

為了遵守 factory function 的規矩，factory function 回傳的物件必須位於 heap (在 function 中被 `new` 出來的)，被 `new` 出來的物件必須手動刪除它。
```cpp
TimeKeeper* ptk = getTimeKeeper();
delete ptk;
```

儘管 [[Smart Pointer|條款13 使用資源管理器]] 和 [[讓介面容易被使用]] 說明了依賴 client 做 `delete` 有潛在的危險跟不確定，這裡要說明的是更嚴重、更根本性的問題。
- 我們宣告的是 **Base class pointer**，指向的是 **child class 物件**。
- Base class 擁有一個 non-virtural 的 destructor
- C++ 明白的告訴我們，當 child 物件經由擁有 non-virtural destructor 的 Base class pointer 持有，而這個 pointer 被刪除時，屬於 **Undefined behavior**

此 Undefined Behavior **通常**會發生的是，屬於 Base class 部分成功銷毀，只屬於 Child Class 的 member data **沒有被銷毀**，造成**部分銷毀**的詭異狀況。

要消除這種作法的解答就是，給 Base class 的 destructor 設置 `virtural`。

> 一個 Class 若有帶有 `virtural` 的函式，幾乎可以確定**該有**會帶有 `virtural` 的 destructor。如果一個 class 不帶有 `virtural` function，通常代表它不意圖被當作 base class。

 (實作都寫完在 base 了，還特意搞繼承 override 幹嘛?)。然而，`virtural` 也不應該亂用: [[Do not Declare Virtural Function in Non-polymorphic Base Class]]。

## 企圖以多型設計架構前，檢查 Base Class 的 Destructor 是否為 Virtual

如果不是 virtural destructor，請想別的辦法!! 
接續前面章節，**並非** class 中沒有 `virtural` function，**就不需要** 考慮 non-virtural destructor 的問題。

以例子來說，若有個 `SpecialString` 繼承 `std::string` (non-virtural destructor)，在 `new` 一個 `SpecialString` 之後指給 `std::string` pointer 之後就會遇到 Undefined Behavior 的問題! 

```cpp
SpecialString *pss = new SpecialString("Impending Doom");
std::string *ps;

ps = pss;
delete ps; // undefined behavior
```

同樣需要注意的如 `std::vector`, `std::list`, `tr1::unordered_map` ([[Item55 Familiarize yourself with Boost]]) 等。如果你想繼承一個 STL container，但它沒有 virtural destructor，請千萬不要嘗試繼承它! 這只會帶來災難。

## 想要一個抽象類嗎
想要一個抽象類，卻苦於沒有人選(function)「被 virtural」? 考慮 Destructor 吧: [[Pure Virtual Destructor]]


