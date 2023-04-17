---
title: "Member Initialization List"
date: 2023-04-10 21:04
tags:
- cpp
---

> 無論如何，使用 member initializer list 對 member data 初始化是最好的。儘管這麼做對內建型別的資料沒差，對非內建型別卻有巨大的意義。

如果你就是想要 call member data 的 default constructor，依然可以透過 member initializer list 達成。只要給予空括號，不填內容即可。
這樣的好處是明白地列出所有 member data，避免有 data 忘記給初始值，特別是對**非內建型別**的member data，沒有初始化的結果是災難的。

對於內建型別的 Reference & const，他們**不能被賦值**，**必須透過 member initializer list 初始化**。
- Related: [[Item5 Know What Functions C++ Silently Writes and Calls]]

## 合理的使用 Assignment
某些時候，類別擁有多個 Constructor，每個 Constructor 都需要有自己的 Member initializer list，這又會導致 dumplicated。
這時候可以是當地將一些 Assignment 和 Initialize 效率差不多的 member data (通常是內建型別)，移到一個 "統一初始化" 的 private function，供所有的 Constructor 呼叫。
這種作法 (pseudo-initialization, 偽初始化) 特別在數值是由讀檔得到的時候特別有用，但可以的話，盡可能使用 member initializer list。
