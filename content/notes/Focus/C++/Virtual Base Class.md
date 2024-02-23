---
title: "Virtual Base Class"
date: 2023-05-23 23:41
tags:
- cpp
---

> 讓鑽石繼承中，帶有該資料的 Base Class 成為 virtual base class。

此例中就是 `File` 要成為 virtual base class，`InputFile` & `OutputFile` 在繼承 `File` 時要加上 `virtual`。
![[Item40_VBC.png]]
C++ STL 裡面有一個這樣的體系，只是他們是 class template 上的繼承關係 (basic_ios, basic_istream, basic_ostream, basic_iostream)。

## 代價

Public 繼承應該總是為 virtual public 嗎?  virtual 有代價
- 存取 virtual base class member data 會比 non-virtual class member data 慢。
- virtual base class 初始化規則複雜、不直觀的多。

## virtual base class 的初始化
由最底層 (most derived class ) 負責
1. most derived class 需要認知到 virtual base class 在哪，它可能很遙遠
2. 一但有新的 derived class 被加入，責任將拋到它身上。

### 忠告
1. 不輕易使用 virtual base class 
2. 如果必須使用，避免在裡面放資料，這樣就不需要擔心初始化與賦值帶來的問題了。
