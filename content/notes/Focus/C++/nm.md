---
title: nm
date: 2024-02-23 12:59
tags:
  - cpp
---


[man](https://linux.die.net/man/1/nm)
[nm 的中文摘錄](https://pxnet2768.pixnet.net/blog/post/69177699)

```
00000000000012d8 t _GLOBAL__sub_I__ZN8test_cls2f3Ev
00000000000012f2 W _ZN8test_cls2f1Ev
00000000000011ca T _ZN8test_cls2f3Ev

```
大寫: Global Symbol，小寫: local symbol。


`W`: The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the symbol is determined in a system-specific manner without error. On some systems, uppercase indicates that a default value has been specified.

`T`
