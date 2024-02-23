---
title: "避免傳回 Handles 指向物件的 Private & Protected Member Data"
date: 2023-05-01
tags:
- cpp
---

> 消滅 handles 的暴露可能


## 大忌: 回傳一個 Non-Const handles 
在 [[打破 Constness 限制#Physical Constness]] 當中，我們探討過 Physical (bitwise) Constness 的問題。
讓 Getter 回傳一個 non-const reference 指向 member data，會出現讓 private data 暴露在外 (等同於 public) 的詭異現象。
此問題不限於 ref，pointer、iterator 這些 handles (用以取得某個物件)，都有相同的風險。

## 回傳一個 Const Handles 就沒問題了嗎?

```cpp
struct RecData {
	Point ulhc;
	Point lrhc;
}

class Rectangle {
public:
	const Point& upperLeft() const {return pData->ulhc;}
}

class GUIObj;
const Rectangle bbox (cosnt GUIObj& obj);

GUIObj* pgo;
const Point* pUpperLeft = &(bbox(*pgo).upperLeft()); // dangling
```

此例的第 15 行，
1. 相當於先創建了 `tmp = bbox(*pgo*)`
2. 對 `tmp.upperLeft()`取得一個 `const Point&` 內部資料 ``
3. 對此內部資料取 address，傳給 `pUpperLeft`
4. 15 行執行完畢，`pUpperLeft` 直接變成 dangling pointer

最大的問題是，**handles 比其所屬的物件更長壽**!! 最簡單的就是消滅 handles 的暴露可能。

但並不意味不能回傳 handles，有時是必須的，像是 `operator[]` 就必須回傳 reference 指向 container 內部元素。





[[Effective C++ Outline#條款3 盡可能使用 const]]
