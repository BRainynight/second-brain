---
title: "了解 Inline 的裡裡外外"
date: 2023-04-10 21:01
tags:
- cpp
---

## 原理
用程式碼取代 function call

## 向 Compiler 發出申請

Programmer 可以明確的提出請求，或隱喻的提出。但編譯器可以拒絕這個申請，大部分過於複雜的函式都會被拒絕 inline:
- 有 loop 的
- 多數的 virtual function (等 Runtime 才確定哪個被喚醒)

顯示與隱式的分別:
- 顯式: 關鍵字 `inline` 是一種對 Compiler 發出的明確請求，但 Compiler 不一定會聽話。
- 隱式: 有另一種暗示請求，就是把 function 實作寫在 class 定義裡面。這種通常是 member function，但 friend function 也可直接定義在 class 內，因此也可能被隱式宣告為 inline。

```cpp
class Person {
public:
	int age() const { return theAge; } 
	// an implicit inline request: age is  defined in a class efinition
private:
	int theAge;
};
```



## 優點
當 inline function 本身很小的時候，把程式碼展開在呼叫者的「函式本體」的成本(object code 大小) ，會比呼叫該 function 所產生的成本來的小! 

## 缺點
1. 當 inline func 函式本體龐大，這些龐大的碼會散布在各個呼叫者的函式本體，導致程式太大。
2. 由於它的表現相當於直接展開在各個呼叫者身上，一旦 inline function 有更改，caller 也會被更動。而 non-inline 就只會是重新連結的問題，對重新 Compile 的負擔比較小。
3. Debugger 沒辦法對付 Inline function --- 怎麼對一個不存在的函式設定中斷點呢?

## Guidline 
- 限制 Inline 使用的時機: 它有絕對的理由必須是 inline (template 規定?) [[Item46 需要型別轉換時請為模板定義非成員函式]]
- 十分平淡無奇，像是 `return m_size` 這般無聊。

## Library Provider 必須謹慎評估是否宣告函式為 Inline 
有關 Inline 帶來的壞處，敘述於 [[建構和解構式是 inline 的糟糕人選]]。

要注意，inline 無法隨著函式庫升級而升級，一旦 inline funciton 內容有變更，Client 端所有有用到該 function 的程式都需要重新編譯。
而若不用 inline，Client 端只需要重新 Link 即可。

## Template and Inline

inline function 通常一定放在 header file 裡面，因為大多數的建置環境會在編譯中做 inlining，為了把 function call 換成「被呼叫函式」本體，必須知道被呼叫函式的內容。

Template 也通常放在 header file，因為一旦使用，Compiler 為了具現化，同樣需要知道其內容。

但 inline 具現化與 template 具現化無關，不過，如果 template 的作者**希望** function 為 inline，應該明確以關鍵字 `inline` 宣告。