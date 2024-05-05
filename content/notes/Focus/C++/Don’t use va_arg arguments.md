---
title: Don’t use va_arg arguments
date: 2024-02-29 21:12
tags:
  - cpp
---
當 Function 需要接受任意數量的輸入的時候，不要使用 `va_arg` (macro)。

[Variadic functions](https://en.cppreference.com/w/cpp/utility/variadic) 是像 `std::printf` 這類可以接受任意數量輸入的 function。

困難的地方在於，寫這種 function 需要**假設**傳入的型態是正確的，但這個假設卻是一個 error prone (錯誤傾向?) 的假設，非常依賴於 Programmer 的紀律。

在 C++17 中，[[Fold Expression]]可以很優雅的解決問題。
