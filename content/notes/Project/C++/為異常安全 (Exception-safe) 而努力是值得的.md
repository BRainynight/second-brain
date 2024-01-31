---
title: "為異常安全 (Exception-safe) 而努力是值得的"
date: 2023-05-01 23:04
tags:
- cpp
---

## 異常安全的條件
1. 不洩漏任何資源
2. 不允許資料敗壞

## Bad Case

先看一個很糟糕的例子: 
```cpp
class PrettyMenu {
public:
...
void changeBackground(std::istream& imgSrc); // change background
... // image
private:
 Mutex mutex; // mutex for this object 
Image *bgImage; // current background image
int imageChanges; // # of times image has been changed
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
lock(&mutex); // acquire mutex (as in Item 14)
delete bgImage; // get rid of old background
++imageChanges; // update image change count
bgImage = new Image(imgSrc); // install new background
unlock(&mutex); // release mutex
}
```

1. 不洩漏任何資源: 第 17 行，一旦 `new` 過程中拋出 exception，第 18 行就不會執行，mutex 永遠不會 unlock。
	- 可透過 smart pointer 管理 heap-based 資源 (created by `new` ) 洩漏問題。
	- 使用 [[Mutex]] 的 `Lock` 確保離開 `changeBackground` 之後，mutex 就會自動解鎖。
```cpp
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
Lock ml(&mutex); // from Item 14: acquire mutex and ensure its later release
delete bgImage;
++imageChanges;
bgImage = new Image(imgSrc);
}
```

2. 不允許資料敗壞: 一旦 `new Image(imgSrc)` 的過程拋出 exception
	1. `bgImage` 會指向一個已經刪除的物件
	2. image 沒有創建成功，`imageChanges` 記數卻已經加上去。
在解決資料敗壞問題之前，先導入 exception safe 的保證

## Exception-Safe Functions
必須提供三者之一
1. 基本承諾: 
	- 如果異常被拋出，程式的任何資料都處於有效的狀態 (只要有效即可，不保證是哪一個 status)。
	- 程式內任何的資料、狀態仍處於前後一致的狀態 -- 但現實中有些不可能，舉例上面的程式，當 `changeBackground` 拋出 exception 時，`PrettyMenu` 物件要使用哪一種背景? 預設背景? 原背景? Client 端需要 query 才知道。
2. 強烈保證: 如果異常被拋出，呼叫者的程式狀態不改變。呼叫異常安全函式者會知道: 函式成功則完全成功，失敗則程式回到「呼叫函式」之前。
	- 這種保證比基本承諾好，Client 不用猜測「合法狀態」是哪一種狀態。
3. 不拋擲 (nothrow) 保證: 承諾決不拋出異常，內建型別 (int, pointer) 身上的所有操作都屬於此類。
	- 要注意，Empty exception specification 不是 nothrow 函式，而是如果此函式拋出異常，將是嚴重的錯誤，會有意想不到的函式 (搜尋 C++ 文件 `set_unexpected`) 被喚起。
	- [[Modern C++ noexcept]]
```cpp
int doSomething() thorw(); // empty exception specification
```

> [!todo]
> P132










