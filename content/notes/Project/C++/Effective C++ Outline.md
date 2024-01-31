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
- [[以 Const 取代使用 Define]]
- [[The definition and declaration of static const]]
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
```cpp
Empty() { ... } // default constructor
~Empty() { ... }
```
- copy constructor, copy assignment
```cpp
Empty(const Empty& rhs) { ... } // copy constructor
Empty& operator=(const Empty& rhs) { ... } // copy assignment 
```

並且，都是 public inline function!! 關於這些 function 被 inline 會帶來什麼危害，見 [[建構和解構式是 inline 的糟糕人選]]。

更確切來說，是當這些 function 被需要 (被呼叫) 時產生: [[Default Generated Functions]]

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

當 Programmer 自己定義 [[Copying Function]] 時，Compiler 不會警告你出錯! 你需要自己注意!!

## Chapter3 資源管理

### 條款13 使用資源管理器

- 資源取得的時機就是初始化的時機 (Resource Acquisition Is Initialization, [RAII](https://zh.wikipedia.org/zh-tw/RAII))
- [[Smart Pointer]] 是個好選擇

### 條款14 仔細考慮資源管理類別的 Copy 行為
- Smart Pointer 那類的資源管理器，適合用來掌握 heap-based resource 的生命週期。
- 並非所有的資源物件，都適合用 Smart Pointer 管理。
- 書中以 [[Mutex]] (互斥鎖) 舉例。

> [!Todo]
> 1. 查一查 RAII，這整個章節我看不太懂。
> 2. 看到 P67，面對複製的問題還沒看。


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

[[讓介面易於被使用，不易誤用]]

### 條款19 設計 Class 猶如設計 Type
設計 Class 請遵守準則想過一遍: [[設計新 Class 的準則]]

### 條款20 以 Pass by Const Ref 取代 Pass by Value 

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
- [[Protected 與 Public 都是低封裝度的 Access Level]]


### 條款23 寧以non-member, non-friend替換 member函數

這條是針對 Object-Oriented C++ 的法則，[[Non-member && Non-friend Function 的封裝度優於 Member Function]]。
站在 Template C++ 又有其他需要考慮的地方，形成了 [[需要型別轉換時請為模板定義非成員函式]]。


### 條款24 如果所有的參數都需要型別轉換，請為此採用 non-member 函式
[[當所有的參數都需要型別轉換，採用 Non-member Function]]


### 條款25 考慮寫出一個不拋異常的 Swap 函式
[[Swap and pimpl]]

> [!danger]
> 讀到 P111，我懷疑 C++11 之後有不同的做法，先不細看。


---

## Ch5 Implementation
### 條款26 盡可能延後變數定義式的出現時間
盡可能等到已經擁有初始值了，再一口氣定義+賦予初始值。如此不必調用多餘的 constructor ! 
- [[盡可能延後變數定義式的出現時間]]


### 條款27 少做轉型動作 (Minimize Casting)
- 如果轉型是必要的，試圖把它隱藏在函式之後，不讓 User 在他們的程式中轉型。
- 作為 Client，如果需要轉型，考慮使用新式的轉型，即使用舊式看起來也合情合理。
[[少做轉型動作(Minimize casting)]]

### 條款28 避免傳回 Handles 指向物件內部成分
[[避免傳回 Handles 指向物件的 Private & Protected Member Data]]，目的是盡可能消滅 dangling handles 出現的可能。


### 條款29 為異常安全 (Exception-safe) 而努力是值得的

[[為異常安全 (Exception-safe) 而努力是值得的]]

> [!Todo]
> Read to P132
 
### 條款30 透徹了解 Inline

宣告 inline 前，先透徹讀完: [[了解 Inline 的裡裡外外]]

### 條款31 將檔案間的編譯依存降到最低
[[將檔案的編譯依存關係降到最低]]


---

## Ch6 繼承與物件導向

### 條款32 確定 Public 繼承塑造出 is-a 關係
[[確保 Derived Class 和 Base Class 之間必然保持 Is-a 關係]]

Public inheritance 意味著 Is-A 關係，Private inheritance 的意義則完全不同 [[審慎的使用 Private 繼承]]。




### 條款33 避免遮掩繼承而來的名稱
當 Base Class 和 Drived Class 有相同名稱的 function 但不同 signature 時，override 不會發生，而是直接覆蓋掉 Base Class 的 function，等同於 Drived Class 的 function 脫離了 Base Class 的掌控，這就是本條款想強調的: 這個行為遮掩了繼承來的名字。

[[使用關鍵字 using 讓特定 function 在 Scope 內可見]]
[[override]]

### 條款34 區分介面繼承與實作繼承
透過 Pure virtual function, Impure virtual, non-virtual function 三種 function 區分 Base Class Designer 的意圖。

[[區分介面繼承(interface)和實作繼承(implement)]]

### 條款35 考慮 Virtual 函式以外的其他選擇
除了 Virtual function，我們還有其他手法可以達到「讓 Derived Class 提供相同的介面、不同實作的手法」
- [[藉由 Non-Virtual Interface 手法實現 Template Method Pattern]]
- [[藉由 Function Pointer 和 tr1 function 手法實現 Strategy Pattern]]

### 條款36 絕不重新定義繼承來的 Non-virtual Function
[[絕不重新定義繼承來的 Non-virtual Function]]

### 條款37 絕不重新定義繼承來的預設參數值
[[靜態綁定 (statically bound) 與動態綁定 (dynamically bound)]]

### 條款38 確定 Composition 塑造的是 Has-A 關係或根據某物實作的關係

Model "has-a" or "is-implemented in terms of " through composition.
[[確定 Composition 塑造的是 'Has-A'關係 或 '根據某物實作'的關係]]

### 條款39 明智審慎的使用 Private 繼承
[[審慎的使用 Private 繼承]]

### 條款40 明智審慎的使用多重繼承
[[多重繼承 (Multiple Inheritance, MI)]]


## Ch7 Template and Generic Programming
[[Template 的用途]]


### 條款41 了解隱式介面和編譯多型
[[Template 與隱式介面]]

### 條款42 了解 typename 的雙重意義
[[關鍵字 typename 在 Template 中的意涵]]

### 條款43 學習處理模板化基礎類別內的名稱
know how to access names in templatized base classes.
[[了解如何在 Template 中指涉 Base Class 成員]]

### 條款44 將與參數無關的程式碼抽離 Templates
[[Template 帶來的程式碼膨脹]]

### 條款45 運用成員函式模板接受所有相容型別
[[運用成員函式模板，接受所有相容的型別]]


### 條款46 需要型別轉換時請為模板定義非成員函式


- [[需要型別轉換時請為模板定義非成員函式]]

### 條款47 請使用 Traits Classes 表現型別資訊

### 條款48 認識 Template 超編程

## Ch8 自訂 new 和 delete

### 條款49 了解 new-handler 的行為

### 條款50 了解 new 和 delete 的合理替換時機

### 條款51 編寫 new 和 delete 時需固守常規

### 條款52 寫了 placement new 也要寫 placement delete



## Ch9 雜項討論
### 條款53 不要輕忽邊義器的警告

### 條款54 讓自己熟悉包刮 TR1 在內的標準函式庫
[[Item54 Familiarize yourself with the standard library including TR1]]

### 條款55 讓自己熟悉 Boost

[[Item55 Familiarize yourself with Boost]]


簡體目錄: https://blog.csdn.net/weixin_45926547/article/details/121276226
