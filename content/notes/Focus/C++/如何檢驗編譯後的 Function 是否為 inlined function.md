---
title: 如何檢驗編譯後的 Function 是否為 inlined function
date: 2024-02-23 12:59
tags:
  - cpp
---


理論上，programmer 不需要知道，這些交給 compiler 決定就好。我根據 [Stackoverflow 的討論](https://stackoverflow.com/questions/10631283/how-will-i-know-whether-inline-function-is-actually-replaced-at-the-place-where)串做了些研究。

但為了釐清某些觀念，我希望知道 function 是否隱性的被 inline、亦或是顯性 inline 是否有被接受。
## Winline
對於那些被標示為 inline，編譯結果卻沒有被 inlined 的 function 而言，在 gcc compile 的命令加上 `-Winline` 即可，這些 function 會以 warning 的形式記錄在 compile log 當中。

## nm
[[nm]] 是 Linux 下一個檢視 object file 內容的指令:
```cpp
nm object_file
```

透過 nm 檢視後面範例的 object file，我得到下面內容 (只擷取與 test_cls 相關的部分): 
```
00000000000012d8 t _GLOBAL__sub_I__ZN8test_cls2f3Ev
00000000000012f2 W _ZN8test_cls2f1Ev
00000000000011ca T _ZN8test_cls2f3Ev
```
也就是說，除了 `f2` 被強制 inline，`f1` 跟 `f3` 都不是 inline function? 但討論串中有人說到，nm 看的並不全面，一個 function 是否被 inline 對不同的 instance call 而言可能有不同的解釋，總之就是有可能不準。

## 看組合語言
使用 `-S` flag 生成組合語言
```bash
g++ -S FileName.cpp
```


## Resource 
- [Godblot](https://gcc.godbolt.org/): 線上轉換組合語言，並有區塊對照! 

## Example 
### inline.hpp
```cpp
#include <iostream>
#include <list>
#include <map>

class test_cls {
public:
    void f1() {
        std::cout<<"f1"<<std::endl;
    }

    __attribute__ ((always_inline))
    void f2() {
        std::cout<<"f2"<<std::endl;
    }

    void f3();
};


```

### inline.cpp
```cpp
#include "inline.hpp"
void test_cls::f3() {
    std::cout<<"f3"<<std::endl;
}

int main() 
{
    auto t = test_cls();
    t.f1();
    t.f2();
    t.f3();
}
```

cmd:
```
g++ -o inline inline.cpp
```