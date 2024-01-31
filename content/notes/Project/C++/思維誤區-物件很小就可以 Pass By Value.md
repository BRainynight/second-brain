---
title: "思維誤區-物件很小就可以 Pass By Value"
date: 2023-04-17 23:25
tags:
- cpp
---
有三個主因: 
1. 並非「該物件/container」**看起來**很小，用 Pass by value 就沒有問題。許多  STL Container 在實作上的大小也就一個 Pointer 大一點，但 Copy Container 卻有「複製每一個 Pointer 所指向的物件」的風險在。
2. 視 Compiler 而定，有些 Compiler 對待 Custom class 跟 built-in class 的態度大不相同，即使底層表述(underlying representation) 相同，仍可能以不同的操作對待，導致 Copy 在 Custom Class 就是比較慢。
3. Type 實作可能發生改變，現在 Copy 的代價不昂貴，不代表以後不會。

## Pass By Value 的代價
[[Pass by value 當中的 Copy 行為]]
