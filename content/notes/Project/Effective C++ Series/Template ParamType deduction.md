---
title: "Template ParamType deduction"
date: 2023-05-18 23:44
tags:
- cpp
---

> `T` is a part of ParamType when it declared in template.

- Case1. [[ParamType 是 Pointer 或 Reference 但不是 Universal Reference]]
- Case2. [[ParamType 是 Universal Reference]]
- Case3. [[ParamType 非 Reference 或 Pointer]]
- Case4. [[Array As an Argument]]
- Case5. [[Function As an Argument]]

## Conclusion

1. 當 Argument 是有 Reference 時，其 Reference-ness (`&`) 會被忽略
2. Universal Reference 在收到 lvalue argument 走的程序是特別的。
3. 做 Pass by value (Copy) 時，常數性(constness) 會消失
4. Function name & array name Argument 會 decay 成 Pointer 進行 template deduction，除非該 template 的 parameter type 是宣告成 Reference。

