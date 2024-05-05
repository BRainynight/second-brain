---
title: invariant class
date: 2024-03-04 22:53
tags:
  - cpp
---
> An invariant is a logical condition for the **members of an object that a constructor must establish for the public member functions to assume**. After the invariant is established (typically by a constructor) every member function can be called for the object. An invariant can be stated informally (e.g., in a comment) or more formally using Expects.


當 class 有 member data 有必須透過 public member function (包含 private data)，就稱為 invariant class。因此 constructor 就是常見的 "public member function"。

對於 Private data，使用者無法在不使用 constructor 的情況下初始化物件，class definer 必須在 constructor 指派 private data，這時就該

這個例子中，`y, m, d` 得透過 constructor 生成，

```cpp
class Date {
public:
    // validate that {yy, mm, dd} is a valid date and initialize
    Date(int yy, Month mm, char dd);
    // ...
private:
    int y;
    Month m;
    char d;    // day
};
```