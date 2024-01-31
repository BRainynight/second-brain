
> This is a quick note 

## Ch2 Philosophy
### 幾乎沒有理由應該遵守的
P.1 Express ideas directly in code 

P.2 Write in ISO Standard C++ 
- 為了兼容，不要寫出依賴於特定架構、特定 Compiler 才可行的 code。
- 小心 [[Undeined behavior and Implementation defined behavior]]

P.3 Express intent 
- 善用 STL [Algorithms library](https://en.cppreference.com/w/cpp/algorithm) ，比起單純的 for loop 改用 std::find 去找值，也表達意圖。
P.4 Ideally, a program should be statically type safe 
P.5 Prefer compile-time checking to run-time checking
- C++14 起添加了 [[Item15 constexpr]] 之類的，可以在編譯期間優化的內容，也新增的編譯期間可用的 assert。如果有編譯期間檢查的，就該在編譯期間確定。
P.6 What cannot be checked at compile-time should be checkable at run-time 
P.7 Catch run-time errors early 
P.8 Don’t leak any resources 
P.9 Don’t waste time or space 
P.10 Prefer immutable data to mutable data 
P.11 Encapsulate (封裝) messy constructs, rather than spreading through the code 
P.12 Use supporting tools as appropriate 
P.13 Use support libraries as appropriate

## Interface
I.2 Avoid non-const global variables 
- 會導致 global variable 在哪裡改動不易察覺。
- [[Drawback of non const global variable]]
I.3 Avoid singletons 
- [[Singleton]]
I.13 [[Do not pass an array as a single pointer ]]
- 優先考慮 std::vector，如果在設計 function 時必須兼容 C-array，則可以考慮 `std::span<T>` (C++20) 作為 signatrue 
I.27 For stable library ABI, consider the Pimpl idiom 
- ABI: application binary interface 
- 對於一個 ABI 開發者，由於對外的 API 會影響 Client 端，盡量用 Pimpl 把實作和 Interface 切分開來。
## Functions (Ch4)
F.4 If a function may have to be evaluated at compile-time, declare it constexpr
- 被宣告成 `constexpr` 的內容會存在 ROM (read only memory)，不會在執行期間 (runtime) 求值、運算，就有如 const 一般，也因此是 thread safe。
F.6 If your function may not throw, declare it noexcept 
- 如果 Function 不應該 thorw exception，則宣告成 noexcept.
1. 這可以減少 client 端所需考慮的情況組合
2. 對於 Optimizer 來說，noexcept 是一個有價值的資訊
3. 即使 function 還是內可能拋出 exception，依然可以宣告 noexcept。這種情況表示: 該 function 並沒有對 exception 做任何控制，程式沒有能力應對 exception。因此會直接呼叫 `std::terminate`。
4. 最後，這可以增加可讀性，使 reader 明白 implemter 的意圖。
[[永遠不該扔例外的 function]]
F.8 Prefer pure functions 
- 給予相同的輸入，必然得到相同的輸出。
- 如果結果 depends on `time`, `random`, 就會是 non pure function 
F.15 Prefer simple and conventional ways of passing information 
- [[Prefer simple and conventional ways of passing information ]]
- 這是一條很大的 rule，後面有很多小條的逐一說明每一種情況。
F.16 For “in” parameters, pass cheaply-copied types by value and others by reference to const 
F.19 For “forward” parameters, pass by TP&& and only std::forward the parameter 
F.17 For “in-out” parameters, pass by reference to non-const 
F.20 For “out” output values, prefer return values to output parameters 
F.21 To return multiple “out” values, prefer returning a struct or tuple 
F.42 Return a T* to indicate a position (only) 
F.44 Return a T& when copy is undesirable and “returning no object” isn’t needed 
F.45 Don’t return a T&& 


F.48 Don’t return std::move(local) 
F.46 int is the return type for main() 
F.50 Use a lambda when a function won’t do (to capture local variables, or to write a local function) 
F.52 Prefer capturing by reference in lambdas that will be used locally, including passed to algorithms 
F.53 Avoid capturing by reference in lambdas that will be used nonlocally, including returned, stored on the heap, or passed to another thread 
F.51 Where there is a choice, prefer default arguments over overloading 
F.55 Don’t use va_arg arguments







----

## 直接在程式碼解釋要做什麼
舉例而言，比起寫一個 for loop 在一個 list 中找到指定的數值，不如使用 `std::find`。
有句諺語是 「如果你使用 explicit loops，代表 你不知道 STL 的 [Algorithms library](https://en.cppreference.com/w/cpp/algorithm)

> A professional C++ developer should know the algorithms of the STL. By using them, you avoid the usage of explicit loops, and your code becomes easier to understand, easier to maintain, and therefore, less error prone. There is a proverb in modern C++: “When you use explicit loops, you don’t know the algorithms of the STL

## 撰寫 ISO 標準 C++ 小心 undefined behavior 和 implementation-defined behavior

[[Undeined behavior and Implementation defined behavior]]


## 確保 Type safe 

原則上，C++ 是靜態定型。但要小心 union, cast, array decay, range error, narrowing conversion 帶來的型態變換。
- union 的問題: C++17 之後可用 `std::variant` 取代
- templated based 的 generic code 可以降低 casting 的需求，進而減少 type error。
- Array decay 通常發生於，呼叫一個 function 並傳入 c array。對 function 而言拿到的是第一個 item 的 pointer (???)。可使用 GSL 避免此類問題。
- narrowing conversion 指有資料損失的隱性轉換。





## What I can do 
- [Algorithms library](https://en.cppreference.com/w/cpp/algorithm)
- 
