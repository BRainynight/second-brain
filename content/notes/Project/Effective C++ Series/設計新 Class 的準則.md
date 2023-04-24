---
title: "設計新 Class 的準則"
date: 2023-04-19 01:00
tags:
- cpp
---
在設計 class 之前，思考以下問題
- 記憶體如何產生跟銷毀? (參見第八章)
- 物件初始化與賦值的差別? Constructor & Assignment
	-  [[Effective C++ Outline#條款4 確定物件在使用前已經初始化 |條款4 確定物件在使用前已經初始化]]
- Pass by value 對它代表甚麼? Copy constructor
- Member data 的合法值?
	- 在不管是 constructor, assignment, setter function 在設 data 時，都需要進行錯誤檢查。
	- 這意味著你需要考量函式拋出的意外。
- 它需要配合某個繼承圖系(inheritance graph) 嗎?
	- 會受到父輩們的約束，特別是函式是 virtural or non-virtual [[Item34 Differentiate between inheritance of interface and inheritance of implementation]]、[[Item36 Never redefine an inherited non-virtual function]]。
	- 如果允許其他類別繼承此 class，請將必要的函式宣告為 virtual，特別是 destructor。
		- [[Effective C++ Outline#條款7 為多型用途的基礎類別宣告 virtual 解構式|條款7 為多型用途的基礎類別宣告 virtual 解構式]]
- 需要考量轉換嗎? 隱性轉換與顯性轉換?
- 甚麼運算子與函式對此新類別式合理的?
	- [[Non-member && Non-friend Function 的封裝度優於 Member Function]]
	- [[當所函式所有的參數都需要型別轉換，採用 Non-member Function]]
	- [[盡可能延後變數定義式的出現時間]]
- 什麼標準宣告式是需要駁回的? 請用 `delete` 明確刪除它。
- 哪些 member 需要暴露出來? (public/private/protected)
- 什麼是它的未宣告介面(undeclared interface)?
	- 這我看不懂。
- 這個新的 class 有多一般化? 若要定義的是 type family (一堆 type) ，是否該採用 class template?
- 