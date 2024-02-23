---
title: Pure function
date: 2024-02-19 22:40
tags:
  - cpp
---

## Pure Function 

> 給予相同的輸出，總是回傳相同的結果，它彷彿一個大個 lookup table 

C++ 並沒有 keyword 讓 programmer 宣告函式為 pure function 
[Pure Functions in C++‬](https://soroush.github.io/en/2020/08/06/pure-functions-in-cpp/)

## Impure function 
- impure function: 包含了 `random`, `time` 之類的。


impure functions are functions such as random() or time(), which can return a different result from call to call. 
To put it another way, functions that interact with state outside the function body are impure.
