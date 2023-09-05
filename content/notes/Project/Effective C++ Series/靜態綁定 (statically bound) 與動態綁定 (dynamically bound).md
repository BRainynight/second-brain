---
title: "靜態綁定 (statically bound) 與動態綁定 (dynamically bound)"
date: 2023-05-17 23:58
tags:
- cpp
---
## 靜態綁定 (statically bound, early binding) 
- Non-virtual function
- Default Parameter
Non-virtual function 是 statically bound，也就是說，由 Base Class Pointer 喚起的物件在呼叫 non-virtual function 時，就只會呼叫 Base Class 的版本，即使 Base Class Pointer 指向的物件是 Derived Class Instance 亦然。
這會形成 [[絕不重新定義繼承來的 Non-virtual Function]] 當中敘述的，由 Base Class Pointer 和 Derived Class Pointer 指向同一個物件，卻導致不同的行為結果這種，非預期中的奇怪狀態。不只是 Pointer 有此問題，Reference 也相同。

## 動態綁定 (dynamically bound, late binding)
- virtual function
virtual function 走的卻是動態綁定 (dynamically bound)，它不受此困擾，不管由 `B*` 或 `D*` 指向物件 `x` (`D` 的 instance)，都會喚起 `D::func`。

## 物件的動態型別與靜態型別

物件分成動態與靜態型別
- 靜態型別 (static type): 宣告時的型別
- 動態型別 (dynamic type): 執行期間所指的物件的型別
![[Item37.png]]

```cpp
Shape *ps; // static type = Shape*
Shape *pc = new Circle; // static type = Shape*
Shape *pr = new Rectangle; // static type = Shape*

ps = pc; // ps’s dynamic type is now Circle*
ps = pr; // ps’s dynamic type is now Rectangle*
```

Virtual function 透過動態綁定而來，因此呼叫 virtual function 時是叫到哪一個 function，是看當下動態型別。
```cpp
pc->draw(Shape::Red); // calls Circle::draw(Shape::Red)
pr->draw(Shape::Red); // calls Rectangle::draw(Shape::Red)
```
然而，參數是靜態綁定的，假設 `Shape::draw` 的預設參數為 `Red`，`Rectangle` 預設參數為 `Green`，而使用 Shape pointer `pr` 不給輸入參數的呼叫 `draw` 時，卻會呼叫 `Rectangle::draw` 但傳入 `Shape::draw` 的預設參數! 

```cpp
// a class for geometric shapes
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	// all shapes must offer a function to draw themselves
	virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle: public Shape {
public:
	// notice the different default parameter value — bad!
	virtual void draw(ShapeColor color = Green) const;
};

class Circle: public Shape {
public:
	virtual void draw(ShapeColor color) const;
};

pr->draw(); // calls Rectangle::draw(Shape::Red)!
```

預設參數由靜態綁定，是 C++ 為了執行效率的考量，在編譯時就已經決定好。
## 以 NVI 手法解決預設參數是靜態綁定帶來的問題
透過 [[藉由 Non-Virtual Interface 手法實現 Template Method Pattern|NVI]] 手法: 以一個 public non-virtual function 呼叫 private virtual function，是給予 virtual funciton 預設參數的好方法。

1. 宣告一個 public non-virtual function，給予預設的輸入參數。基於繼承的 Is-A 關係，這個 function 不會被 override。
2. 定義一個 pure virtual function，讓 Derived Class 繼承介面，自行實作。
3. 在 public non-virtual function 當中呼叫該 pure virtual function，並把預設的參數傳入。

如此一來，將不會有 Derived Class 擅自改寫預設參數的問題。

