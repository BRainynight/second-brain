---
title: "Pure Virtual Function"
date: 2023-05-13 11:47
tags:
- empty
---

> 只繼承 Interface 需自行實做

相當於告訴 Client: 你需要提供一個這樣的函式，但我不干涉你怎麼做它。
```cpp
class Shape {
public:
	virtual void draw() const = 0;
};
```

不過，我們其實可以為 Pure Virtual Function 提供一份實作碼，只是需要通過 Class Name 呼叫 (以 `Shape::draw` 而非 `shape.draw` 呼叫)，這樣既可以提供一份預設內容，又可以強制 Derived class 要自行實作 (自行 call `Shape::draw`)。

而對於 `Shape` ，它擁有一個 pure virtual function，也就是說它自身永遠不可能被實例化。即使提供實作，也不能直接由 `ps->draw()` 這樣調用。

```cpp
Shape *ps = new Shape; // error! Shape is abstract

Shape *ps1 = new Rectangle; // fine
ps1->draw(); // calls Rectangle::draw
ps1->Shape::draw(); // calls Shape::draw
```
