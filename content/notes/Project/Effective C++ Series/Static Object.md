---
title: "Static Object"
date: 2023-04-10 21:04
tags:
- cpp
---

> 壽命從被建構出來，持續到程式結束為止。

因此 Stack 和 Heap-based 物件都不是 static object。
這種物件包含 Global Object，定義在 Namespace Scope 的物件，Class & Function & File 內宣告成 `static` 的物件。
- Function 內的 static object 稱為 local static object (Scope 只在 function 內)
- 其他被稱為 non-local static object
它們的 deconstructor 會在 main 結束時被喚起。

當我們有兩個編譯單元([[Translation Unit]])，通常表示兩份 Source Code。兩份 Source Code 中都有 non-local static object，且其中一份 static object 的初始化需要使用到另一份 source code 的 static object。

問題在於，有可能要被使用的那個物件尚未被初始化! 
> C++ 對於不同 [[Translation Unit]] 中 non-local Static object 初始化的順序並沒有明確的定義。
> The relative order of initialization of non-local static objects defined in different translation units is undefined.

這是有原因的，因為決定這個順序非常困難，近乎無解，甚至不值得去找解。

這種問題常見於[[Implicit TemplateInstantiation]] 模板隱式具現化。 (? 不確定翻譯)

## Make Non-local Static Object become Local Static Object

> C++ 保證，函式內的 Local static object 會在該函式被呼叫期間，首次遇到該物件的定義式時初始化。

我們可以利用此原則，解決 dependency of 2 non-local static object in 2 different translated units 的問題。

> 將每個 non-local static object 搬到專屬的 function 內，以 local static object 的方式存在。Design Pattern 中的 [[Singleton]] 就式常見的實作方式。

其原理在於，所以比起直接呼叫 non-local static object，使用 function call 的做法更佳。更棒的是，若你從未呼叫「模擬該 non-local static object 的 function」，則 「那個 object 」根本**不會初始化**，有延遲初始化的功效在! 這是真正的 non-local static object 所不能及的。

`static` 可以確保唯一性，Singleton 本身就常常與 Static 搭配使用。

```cpp
class FileSystem { ... };

FileSystem& tfs()
{
    static FileSystem fs;
    return fs;
}

class Directory { ... };
Directory::Directory( params )
{
    std::size_t disks = tfs().numDisks();
}  

// The first call function.
Directory& tempDir()
{
    static Directory td( params );
    return td;
}
```
此種手法稱為 reference-returning。

在此例子中，`tmpDir` 創建物件 `td`，在 call `Directory` Constructor 時，會再 call `tfs` ，此時才創建 static object `fs`。透過 function call，確保了物件初始化的順序，先初始化 `fs`，再創建 `td`。

### 優點
特別在頻繁呼叫的時候，搭配 [[Item30 Understand the ins and outs of inlining]]。

### 缺點
在 multi-thread 中有不確定性。任何一種 non-const static 物件如果**依賴於其他事件的發生**，都很麻煩。常見的解決方法是，在 single-threaded startup portion 手動喚起所有 reference-returning function，手動解決 race conditions。
