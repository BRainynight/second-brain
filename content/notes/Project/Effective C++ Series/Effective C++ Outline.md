---
title: "Effective C++ Outline"
date: 2023-04-10
tags:
- cpp
---
## Chapter 1

### 條款1 C++ 是一個語言聯邦
C++ 融合了多種形式的 programming 手法，物件導向、procedural、generic、metaprogramming、functional...。

### 條款2 盡量以 `const` , `enum`, `inline` 取代 `#define`
- 以 const, enum, inline 取代 `#define`， 寧可以編譯器 (compiler) 取代前處理器 (pre-processor)。 
- 對於單純的常數，以 `const` 或 `enum` 取代
- 對於形似 function 的巨集(macro)，用 `inline` 取代。
#### Const
- [[Replace define with const]]
- [[The definition and declaration of static const]] P14
#### Enum
- [[enum hack]]
#### Inline


### 條款3 盡可能使用 const
盡可能的使用 `const`，它可以確保物件不被改變。特別是 custom class designer 更加需要注意 operator 的 constness。

- `const` 在星號左邊: 被 point 的物件是常數
- `const` 在星號右邊: pointer 自身是常數
```c++
char greeting[] = "Hello";
char* p greeting;

const char* p = gretting; // non-const ptr, const data
char const* p = gretting; // same 

char* const p = greeting; // const ptr, non-const data
const char* const p = greeting; // const ptr, const data
```

當 `const` 在 `*` 前，不管是先寫 const 修飾的類、或是先寫 const 都是一樣的，就是在修飾 `char` 物件具有常數性。
[[Const in C++]]


### 條款4 確定物件在使用前已經初始化
不是所有的物件宣告時自帶初始化，它的規則過於複雜，只需要謹記: 宣告時就要初始化!
(通常是 C-style 的，像是 array 不保證會發生初始化)，而 non-C part 的 (like `std::vector`) 有其他規則，就自帶初始化)

對於內建型別 (int, char, double)，初始化就是手動給值。對於內建型別之外的，則要寫 constructor。

為了避免沒有初始化帶來的不確定性，確保三件事
1. 對於不是 member data 的 built-in type object，手動初始化。C++ 並不保證會初始化所有的 Built-in type Object (ex. array)。
2. 對於 Custom Class，使用 [[Member Initialization List]] 初始化 member data。原因參見 [[Identify Initialization and Assignment]]
3. 若初始化順序具有不確定性，想辦法加強 design，確保不會發生 circle (兩個變數相互依賴) 或競速問題。
4. 當 static object 之間有依賴關係時，local static objects 勝過 non-local static objects。參見 [[Static Object]]

## Chapter2 建構、解構、賦值運算

### 條款5 了解 C++默默編寫並呼叫哪些函式
當我們宣告了一個 Class，而不去實踐任何細節，Compiler 會偷偷地幫我們生成一些 function，他們分別是
- default constructor, destructor
- copy constructor, copy assignment
且都是 public inline function - [[Item30 Understand the ins and outs of inlining]]

更確切來說，是當這些 function 被需要 (被呼叫) 時產生。
[[Default Generated Functions]]

### 條款6 明確拒絕不要編譯器自動生成的函式
在 C++11 引入了新的概念 [Deleted functions](https://www.ibm.com/docs/en/zos/2.4.0?topic=definitions-deleted-functions-c11)，書中教的方法依然有其壞處。直接在 declaration 後面接著 `=delete` 就可以阻止 copmiler 生成它。

```cpp
A(const A&) = delete;
```

[[Deleted Function]]

### 條款7 為多型用途的基礎類別宣告 virtual 解構式
申明，這條規則**只針對**多型的 Base Class
- 首先就先說明多型的用意: [[為多型用途的基礎類別宣告 virtual 解構式]]

### 條款8 不讓異常逃離解構式
C++ 不會禁止 Exception 發生於 Destructor，但這麼做具有相當的風險。一旦 Exception 發生而跳出了 Destructor，會中止銷毀物件的程序。
特別是 STL Container 或 Array 這種資料結構中，若前面有某個 element 在銷毀過程中 thorw Exception 使得 Container 的 Destructor 被中斷，則後面的 elements 有可能不被銷毀，而導致記憶體洩漏! 

[[解構式與異常]]

### 條款9 不在建構與解構中呼叫 virtual 函式

不要在 Constructor 與 Destructor 中呼叫 virtural 函式。這和 Java 與 C# 不同!!!

[[Virtual Function]]


### 條款10 讓 operator= 回傳自身的 reference
讓 `operator=`, `operator+=` 等 assignment 符號回傳自身的 Reference。
這是一項協議，並非強制規定。但在 STL 提供的型別，或是即將 support 的 type ([[Item54 Familiarize yourself with the standard library including TR1]])，都會遵守這個協定，請從眾。

### 條款11 在 operator= 處理自我賦值

在撰寫 `operator=` 時，需要考量當 `rhs==this` 的狀況。
即使不是如下面的方式 handle 自我賦值，記住，不要讓這個函式 raise exception (exception safety) 就對了。

```cpp
Widget& Widget::operator=(const Widget& rhs)
{
	if (this == &rhs) return *this; // assignment to self
	delete pb;
	pb = new Bitmap(*rhs.pb);
	return *this;
}
```

### 條款12 複製物件時記得每一個部分

當 Programmer 自己定義 [[Copying function]] 時，Compiler 不會警告你出錯! 你需要自己注意!!

## Chapter3 資源管理

### 條款13 使用資源管理器

- 資源取得的時機就是初始化的時機 (Resource Acquisition Is Initialization, [RAII](https://zh.wikipedia.org/zh-tw/RAII))
- [[Smart Pointer]] 是個好選擇

### 條款14 仔細考慮資源管理類別的 Copy 行為

- 有些資源並不是 Heap-based Resource，就不一定適合 auto_ptr。
- 書中以 Mutex (互斥鎖) 舉例。

> [!Todo]
> 查一查 RAII，這整個章節我看不太懂。


> [!question]
> (此處是舊版，新版有對應的東西嗎?

### 條款15 在資源管理類中提供對原始資源的存取

儘管使用 [[Smart Pointer]] 管理資源很方便，我們仍有機會需要取得原始的 Pointer。Smart Pointer 同時有提供顯示介面 (explicit) 與隱式介面: 
- explicit : 以 `get` 取得 Raw Pointer。
- implicit : `operator*`, `operator->`。

### 條款16 成對的使用 `new` 和 `delete` 並採用相同型式
1. 盡可能不要用 C-style Array
2. STL所提供的 vector, string 等 templates 可以降低對 Array 的需求，減少錯誤的發生。


### 條款17 以獨立的語句將物件放入 Smart Pointer

```c++
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
```

[[為什麼要用獨立句將物件放入 Smart Pointer]]

## Chapter 4 設計與宣告
### 條款18 讓介面容易被使用、防範誤用

[[讓介面容易被使用]]

### 條款19 設計 Class 猶如設計 Type
設計 Class 請遵守準則想過一遍: [[設計新 Class 的準則]]

### 條款20 以 Pass by const ref 取代 Pass by value 

合理的 Pass by value 幾乎只有下面三種選擇
1. 內建型態
2. STL Iterator 
3. Function Object

除此之外，包含 STL Container 應盡可能用 Pass by const reference !
- [[思維誤區-物件很小就可以 Pass By Value]]

### 條款21 當必須回傳物件時，不要考慮回傳 Reference 

絕對不要
 1. 將 Pointer 或 Reference 指向一個 local 物件回傳。
 2. 讓 Reference 指向 heap-based object (`new`)
 3. 當設計出「回傳 ptr/ref 指向 local static」，並且有很多個物件都採用這種形式時提高警覺，很有可能走入了 Bad design。對於怎麼樣是「合理」使用 Local static object : 參見 [[Static Object]]。


### 條款22 將成員變數宣告成 Private

- 只提供必要的 Getter 給客戶端，隱藏你的實作有絕佳的好處。

思維誤區: Protected 不比 Public 具有更好的封裝性
- 取消一個 Public Member Data 的成本: 所有使用他的客戶端
- 取消一個 Protected Member Data 的成本 : 所有繼承他的 Derived Class
這兩種 Access Level 的封裝性都不佳，仍該盡可能的使用 Private。

### 條款23 寧以non-member, non-friend替換 member函數

[[Non-member && Non-friend Function 的封裝度優於 Member Function]]



### 條款24 如果所有的參數都需要型別轉換，請為此採用 non-member 函式
[[Item24 Declare non-member functions when type conversions should apply to all parameters]]


### 條款25 考慮寫出一個不拋異常的 Swap 函式


## Ch5 Implementation

### 條款26 盡可能延後變數定義式的出現時間
[[Item26 Postpone variable definitions as long as possible]]

### 條款2

### 條款2






簡體目錄: https://blog.csdn.net/weixin_45926547/article/details/121276226
