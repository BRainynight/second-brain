---
title: Do not pass an array as a single pointer
date: 2024-01-14 21:00
tags:
  - cpp
---
不要直接把 C-array 以 Pointer 的方式到處傳遞，這很容易導致 Undefined Behavior。

例如: Copy 的時候忘記幫末位留一個空位，導致差一錯誤 (off-by-one error, 計數時由於邊界條件判斷失誤導致結果多了一或少了一的錯誤)。

迴避的方式很簡單，直接使用 STL container。像是 std::vector，
- 同樣可以用 `operator[]`
- 直接以 member function `size` 

甚至 C++20 提供 `std::span` 可以更優雅的解決此問題: 

span 像是一個 wrapper，用來 refer to  "sequential contiguous container" (ex.  C-array, std::vector) ，然而它不是 owner，不應該有物件的 memory 放在 span 身上。

透過 std::span 的 API，可以直接對 C-array 做 `begin`, `front`, `at` ... 等 STL 的常見 member function。

