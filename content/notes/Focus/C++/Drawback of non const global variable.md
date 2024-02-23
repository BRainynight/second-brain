---
title: Drawback of non const global variable
date: 2024-01-05 00:32
tags:
  - cpp
---
1. 單元測試: 當每個 function 都用到同一個 global variable ，根本抽不出單元，只能做整體測試。
2. 重構: Code 之間不是獨立的，很難抽出來。
3. Performance Optimization: 難以用 multiple thread 之類的手段，因為各個部份之間對同一個 global variable 有 dependency。
4. Concurrency: 可能會有競速 (data race) 問題。
