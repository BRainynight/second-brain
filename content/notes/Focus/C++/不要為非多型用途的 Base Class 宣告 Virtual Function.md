---
title: "不要為非多型用途的 Base Class 宣告 Virtual Function"
date: 2023-04-10 22:18
tags:
- cpp
---

> 無端將不該擁有 `virtual` 的 class 宣告 virtual，與無端將所有的 function 宣告成 virtual，都是有毒的。 

當類別不作為 Base Class，或是不作為多型時的基本 Class 時，不應該使用 virtual。
原因是，`virtual` 背後是以 vptr (virtual table pointer) 和 vtbl (virtual table) 實作 virtual，需要耗費額外的記憶體。
1. 將不能把資料結構式傳給其他語言 (C, FORTRAN) 撰寫的 function，因為它們沒有 vptr 的對應內容
2. 增加物件大小，書中舉例一個 `Point` 物件，其中擁有兩個 int (64bits, in 32 bits system)，增加一個 `virtual` (一個 vptr) 將使 memory 達到 96 bits，相當其物件大小的 50%，在 64bits system 甚至達到增加 100%。
