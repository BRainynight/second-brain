---
title: Parameter Pack
date: 2024-02-20 23:41
tags:
  - cpp
---

When the ellipsis `...` is on the left of the type parameter T1, the parameter pack is packed; when on the right, it is unpacked. 

This unpacking in the return statement `T(std::forward<T1>(t1)...)` essentially means that the expression `std::forward<T1>(t1)` is repeated until all arguments of the parameter pack are consumed and a comma is put between each subexpression. 

For the curious, [C++ Insights](https://cppinsights.io/s/ad5b8b5d) shows this unpacking process.
