---
title: "ParamType 是 Universal Reference"
date: 2023-05-18 23:46
tags:
- cpp
---
當 ParamType 被宣告成 `T&&` (Universal Reference) 時，傳入的變數是 rvalue 或 lvalue 在推斷的流程是**不同的**。詳細在 [[Item24 Distinguish universal references from rvalue references]] 會說明。

原則是: 
 1. 當傳入的是 lvalue，`T` 和 `ParamType` 都會推斷成 lvalue reference type。注意，在 Case 1. 當中，`T` 的推斷是不會保留 reference part 的。
 2. 當傳入的是 rvalue，則規則有如 [[ParamType 是 Pointer 或 Reference，但不是 Universal Reference]]