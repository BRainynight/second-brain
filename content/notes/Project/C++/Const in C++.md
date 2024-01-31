---
title: "Const in C++"
date: 2023-04-10
tags:
- cpp
---

#### Const Iterator
同理上述，宣告一個 iterator 為 `const` 表示這個 iterator 不能改變指向的對象，但是指向的對象之內容本身可以變。 
```cpp
const std::vector<int>::iterator iter = vec.bgein();
```
如果想要指向一個不可被改變內容的物件，需要使用 `const_iterator`
```cpp
std::vector<int>::const_iterator citer = vec.bgein();
```

#### Return Const Value
[[讓介面易於被使用，不易誤用#Return Const Value]]

#### Const member function
[[Const member function]]

#### Const Argument
在真實的程式設計中，比較多用於 function argument 是 const pointer / const referecne。
如下例: `print` function 定義了一個 const reference 的 argument，當它在調用 operator `[]` 的時候，就會用到上面的 API。且定義 const return value 可以避免錯誤的寫入值，達成 const object 的目的。
```cpp
void print(const TextBlock& ctb) // in this function, ctb is const 
{ 
	std::cout << ctb[0]; // calls const TextBlock::operator[] 
	ctb[1] = 'x';        // raise error!!!
}
```

#### 打破 Constness 限制
前面說的是對於 Client 端，我們須保持資料的不可變動性。

然而在類別內部的設計中，基於維護性、或某些理念，我們希望它不要那麼死板，比起 Compiler 所堅持的 Constness，或許邏輯上的 Constness 更加重要。接下來，將說明 Compiler 認知 Constness 為何 ，與如何「部分的」打破 Const 限制。
[[打破 Constness 限制]]
