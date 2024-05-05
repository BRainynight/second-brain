---
title: 必須使用 Class 而非 Struct 的情況
date: 2024-03-04 22:34
tags:
  - cpp
---
## 透過 Member Data 決定: invariant 使用 class, member 之間互相獨立用 struct 

常見的[[invariant class]]: 有 private data 必須透過 constructor 創建其實體 (object)。

Data member 之間互相獨立用 struct

```cpp
struct Pair { // the members can vary independently
   string name;
   int volume;
};
```

## 如果 Implementation 跟 Interface 會分開，就用 Class 
Interface 表示不動的部分，Implementation 是會動的部分。
