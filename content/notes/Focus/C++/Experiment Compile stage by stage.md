---
title: Experiment Compile stage by stage
date: 2024-02-23 12:58
tags:
  - cpp
---

https://www.cs.nmsu.edu/~jcook/posts/c-compiling-linking/


Generate object file only 
```bash
g++ -c *.cpp
```

Generate binary by object file
```cpp
g++ -o prog *.o
```

## Include Guard

> Avoid function redefinition and circling including (?)

Include guard 可以避免相同的 header 被重複 include，以 "add.hpp" 和 "add.cpp" 為例，在沒有 include guard 的情況下，如果 
- add.hpp: `include print_np.cpp`
- add.cpp: `include add.hpp`

則光是編譯 add.cpp 就會出現問題 (`g++ -c add.cpp`)，這種 redefinition 是在單一 translate unit 內就會發生的。
![[Pasted image 20230919231828.png]]

而如果改用有 include guard 的 header，則 add.cpp 的編譯會通過。這是因為 Include Guard 可以確保該 header file 只被 include 一次，這樣 hpp 裡面有被定義的 function 就不會有 redefine 的問題。
- add.hpp: `include print.cpp`

## Multiple Definition
加上 include guard 後，`g++ -c` 可以成功產出 `*.o` 檔案，每一個 object file 相當於一個 translation unit。表示單一 translation unit 已經沒問題了，下一步是把 object file 綁在一起，變成一個可執行的 program。

```bash
g++ *.o
```

這時候遇到新的問題: multiple definition，也就是違反了 [[One Definition Rule]]，main.cpp, minus.cpp. print.cpp 各自都有一個 `print`，linker 不知道怎麼辦。

![[Pasted image 20230923114619.png]]

## Inline 
[[Inline and Translation Unit]]





```cpp
inline void print() { std::cout<<"It causes problem."<<std::endl; }
```