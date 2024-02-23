---
title: "Singleton"
date: 2023-04-10 21:04
tags:
- empty
---

## Drawback of Singleton 
- 誰負責銷毀它?
- 這個 singleton 應該可以被繼承嗎?
- 怎麼實作 singleton 使它 thread-safe 
- 如果 singleton 之間有相依性，而且在不同的 translation unit，順序應該是? 

[What’s the “`static` initialization order ‘fiasco’ (problem)”?](https://isocpp.org/wiki/faq/ctors#static-init-order)


## Use Dependency Injection to resolve singleton dependency 

如果物件必須用到 singleton ，代表這個物件與 singleton 之間隱藏著 dependency。

比起直接在 function 內呼叫 singleton，將需要的內容透過  argument 、透過 setter 、template argument 等方式設進來，可以把依賴阻隔在真正的內容之外。

透過 [[Dependency Injection]]，把與 singleton 的依賴留 arguemnt.
