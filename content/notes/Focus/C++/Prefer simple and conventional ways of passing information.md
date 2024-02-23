---
title: Prefer simple and conventional ways of passing information
date: 2024-01-14 21:41
tags:
  - cpp
---
## 如何決定 Function Signature 的長相

- headings: 資料結構 copying 跟 moving 的成本
- row: parameter 的性質
	- In & retain copy: 在 function 內部會發生 copy 
	- In & retain "copy": Moved-from means that it is in a valid but not nearer specified state.
	- In/out: 在 function 會被變更內容
	- out: 透過 function 所產生的回傳值
後面會有更多 rule 說明這些東西
![[Pasted image 20240114215359.png]]

案例
- 當 Copy 很輕鬆，或不可能發生 Copy 的時候，pass by copy 沒問題: int, std::uniqure_ptr。
- Move 的成本低: `std::vector`, `std::string`
- Move 的成本適中: `std::array<std::vector>` or BigPOD (POD stands for Plain Old Data—that is, a class without constructors, destructors, and virtual member functions.)
- 不知道 Move 的成本: Template。
## "in" parameter 
1. 只有非常「便宜」的才 pass by copy 
2. 其他用 `const & `

C++ Core guideline 提供一個標準衡量 copy 物件是否足夠「便宜」  
> 當 `sizeof(parm) < 3*sizeof(void*)`

## "forward" Parameter 
這種參數對 lvalue 做 copy，rvalue 做 move。constness 在 lvalue 被忽略，但保留於 rvalue。

forwarding parameter 通常用於[[工廠函式 (Factory Function)]] --  像是透過一個 construct function 生成任意物件


```cpp
template <typename T, typename ... T1>  // parameter pack 
T create(T1&& ... t1) {
   return T(std::forward<T1>(t1)...);
}
int main() {
   // lvalue
   int five=5;
   int myFive= create<int>(five);

   // rvalues
   int myFive2= create<int>(5);

   // no arguments
   int myZero= create<int>();

   // three arguments; (lvalue, rvalue, rvalue)
   MyType myType = create<MyType>(myZero, 5.5, true);
}
```
Related syntax: [[Parameter Pack]]

Forward argument 與 template 結合的最好範例就是 `std::make_unique`。

```cpp
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
std::make_unique<T> creates a std::unique_ptr for T
```

## "in-out" Parameters 
在 function 中會更動 object 的數值，因此應以 non-const reference 傳遞。




## 資源所有權 Ownersip Semantics for Parameter Passing

"Ownersip Semantics" 直翻 "所有權語義"，在談論不同的 Parameter type 宣告下的「資源所有權」。

|  |  |
| ---- | ---- |
| Pass by Copy | Function 直接擁有資源 |
| Pass by pointer | Function "借用(borrow)" 此資源，使用前應確認 pointer 非 Null，它「應當」無權釋放資源。   |
| Pass by reference | 同樣 "借用" 資源，但 reference 永遠是 valid value。 |
| func(std::unique_ptr) | `func` 是資源的新擁有者 (owner)，互叫此 `func` 的 caller 相當於把 ownership 轉移給 `func` (callee)，並且資源會在 function 結束時 release。 |
| func(std::shared_ptr) | `func` 是新增的資源擁有者，他延長了資源的 lifetime。`func` 在離開前，會把自己的擁有權從資源刪掉，如果它是最後一個擁有者，則資源會在 `func` 離開時 release。 |

弄清楚誰是資源的 owner 至關重要，以下面這個範例，誰應該是資源 `ptr` 的擁有者? (誰應負責 delete resource? )

按照前面的分配，`func` 是 pass by pointer，它可以改寫內容、可以讀取，但不應刪除資源。

我想這一段在說明的是一個「準則」，讓大家一起 follow 這段準則，避免資源所有權混亂造成記憶體洩漏。更方便的做法，不外乎別用 C-array，多用 smart_ptr .... 。

```cpp
void func(double* ptr) {...}; 

double* ptr = new double []; 
func(ptr);
```


[[How to Pass Output Value]]