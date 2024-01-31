---
title: "Protected 與 Public 都是低封裝度的 Access Level"
date: 2023-05-07 14:18
tags:
- cpp
---

思維誤區: Protected 不比 Public 具有更好的封裝性
- 取消一個 Public Member Data 的成本: 所有使用他的客戶端
- 取消一個 Protected Member Data 的成本 : 所有繼承他的 Derived Class
這兩種 Access Level 的封裝性都不佳，仍該盡可能的使用 Private。