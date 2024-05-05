---
title: Type Safety
date: 2024-03-24 22:05
tags:
  - cpp
---
原則上，C++ 是靜態定型。但要小心 union, cast, array decay, range error, narrowing conversion 帶來的型態變換。
- union 的問題: C++17 之後可用 `std::variant` 取代
- templated based 的 generic code 可以降低 casting 的需求，進而減少 type error。
- Array decay 通常發生於，呼叫一個 function 並傳入 c array。對 function 而言拿到的是第一個 item 的 pointer (???)。可使用 GSL 避免此類問題。
- narrowing conversion 指有資料損失的隱性轉換。