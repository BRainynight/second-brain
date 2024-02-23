---
title: "ODR use"
date: 2023-09-05 23:24
tags:
- cpp
---
https://en.cppreference.com/w/cpp/language/definition#ODR-use

- 當一個物件被稱為 odr use: 物件被讀取 (例外: compile time constant) 或寫入、它的 address 被取用，或有 reference 綁到他身上
- 當一個 reference 被稱為 odr use: 當它所 reference 到的物件在 compile 期間是未知的
- 一個 function 被稱為 odr use: 有產生對它的 function call，或它的 address 被取用
總結: 當一個物件、reference 或 function 被稱為 odr use，表示它的定義必定 exist 於 program 的某處，違反這一點會導致 Link time error。