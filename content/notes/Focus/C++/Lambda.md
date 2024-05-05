---
title: Lambda
date: 2024-02-22 08:52
tags:
  - cpp
---
如何決定該使用 Lambda 還是 Function: 
1. 只會使用到 local variable  或只宣告於 local scope: 使用 lambda 
2. 必須 support overloading: 直接選擇 function. 

使用 Lambda 的時候要注意資料的有效性，Pass by copy / Pass by reference 在 lambda 也有準則

- 當 lambda function 只在該段 local scope 被使用，則 Pass by reference 
- 當 lambda function 不只在 local 被使用，它可能被作為回傳物件、存在 heap，或被傳到 thread 去，則 Capture variable 的方式都應該 Pass by Copy.