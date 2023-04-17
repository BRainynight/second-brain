---
title: "Replace define with const"
date: 2023-04-10 21:04
tags:
- cpp
---

## 以編譯器取代前處理器

 `#define` 的本質是 word replacement，如: `#define RATIO 1.653`，編譯器可能不認得 `RATIO` 並在錯誤訊息中從頭到尾以 1.653 取代 `RATIO`。
```cpp
 const double Ratio=1.653; // Prefer
```

當以 `const` 取代 `#define` 時，有兩個需要注意的點
1. 定義常數指標 (const pointer): 常數指標用於 「不允許此Pointer更改指向的對象」，因此需要對 pointer 宣告 const

```cpp
const std::string = authorName("Scott");
 ```

2. Class 的專屬常數: 目的是限制常數的 Scope，因此要宣告在 class 內部。而為了使這個常數只有一個實體(所有 instance 共享同一個常數)，還需要宣告 `static`。

```cpp
class Player {
private:
	static const int num = 5;
	int scores[num];
}
 ``` 


## 具有 Access Level
第二點的用途，設置一個在某特定類別才生效的常數變是 `#define` 做不到的，`#deinfe` 不在乎 scope，不能帶來封裝性，更沒有 `private #deinfe` 這種東西。
