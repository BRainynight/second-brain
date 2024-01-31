---
title: Translation Unit and Linkage
date: 2023-09-18 19:23
tags:
  - cpp
---
https://learn.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=msvc-170

一個 program 是由一個或多個 translation unit 組成，一個 translation unit 則由一個 implementation file (cpp) 和它使用到的所有 header file (hpp) 所組成。

每一個 translation unit 可以被獨立編譯，當所有的 translation unit 都編譯完成，linker 會把 translation units 融合成一個 Program。違反 [[One Definition Rule]] 會在這個階段爆出 linking error，其原因是有同名稱的 symbol 被定義了多次。


通常，讓一個 variable 在多個檔案之間可見，就是宣告它於一個 header file，將會使用到這個變數的 cpp 都 include 該 header file。透過在 header file 添加 include guards，你可以確保這個 symbol 在一個 translation unit 當中只會被宣告一次。並且，只在一個 cpp 當中撰寫它的實作。

[[Internal and External Linkage]]