---
title: C++ Core Guidelines
date: 2024-02-23 13:02
tags:
  - cpp
  - moc
---


> This is a quick note 

## Ch2 Philosophy
### 幾乎沒有理由應該遵守的
1. 直接在 code 中解釋邏輯
2. 以 ISO Standard C++ 為標準撰寫
	- 為了兼容，不要寫出依賴於特定架構、特定 Compiler 才可行的 code。
	- 小心 [[Undeined behavior and Implementation defined behavior]]
3. 表達意圖
	- 善用 STL [Algorithms library](https://en.cppreference.com/w/cpp/algorithm) ，比起單純的 for loop 改用 std::find 去找值，也表達意圖。
4. 理論上，程式應該保持 [[Type Safety]] 
5. 比起 runtime checking，傾向於 Compile time checking。
	- C++14 起添加了 [[Item15 constexpr]] 之類的，可以在編譯期間優化的內容，也新增的編譯期間可用的 assert。如果有編譯期間檢查的，就該在編譯期間確定。
6. 不能再 compile time checking 的，應該也要有辦法在 runtime checking 
7. 盡早捕捉 runtime error 
8. 相較於 mutable data，傾向使用 immutable data

P.1 Express ideas directly in code 
P.2 Write in ISO Standard C++ 
P.3 Express intent 
P.4 Ideally, a program should be statically type safe 
P.5 Prefer compile-time checking to run-time checking

P.6 What cannot be checked at compile-time should be checkable at run-time 
P.7 Catch run-time errors early 
P.8 Don’t leak any resources 
P.9 Don’t waste time or space 
P.10 Prefer immutable data to mutable data 
P.11 Encapsulate (封裝) messy constructs, rather than spreading through the code 
P.12 Use supporting tools as appropriate 
P.13 Use support libraries as appropriate

## Interface
### 避免 Non-const globale Variables
I.2 Avoid non-const global variables 
- 會導致 global variable 在哪裡改動不易察覺。
- [[Drawback of non const global variable]]
I.3 Avoid singletons 
- [[Singleton]]

### 不要以 Single Pointer 傳遞 Array 
I.13 [[Do not pass an array as a single pointer ]]
- 優先考慮 std::vector，如果在設計 function 時必須兼容 C-array，則可以考慮 `std::span<T>` (C++20) 作為 signatrue 
### ABI 的開發者應考慮使用 Pimpl 切割實作與 Interface
I.27 For stable library ABI, consider the Pimpl idiom 
- ABI: application binary interface 
- 對於一個 ABI 開發者，由於對外的 API 會影響 Client 端，盡量用 Pimpl 把實作和 Interface 切分開來。
## Functions (Ch4)
### constexpr function : 在 compile time 求值，帶來 thread safe 
F.4 If a function may have to be evaluated at compile-time, declare it constexpr
- 被宣告成 `constexpr` 的內容會存在 ROM (read only memory)，不會在執行期間 (runtime) 求值、運算，就有如 const 一般，也因此是 thread safe。
### noexcept: 為 exception safety 提供更多資訊
F.6 If your function may not throw, declare it noexcept 
- 如果 Function 不應該 thorw exception，則宣告成 noexcept.
1. 這可以減少 client 端所需考慮的情況組合
2. 對於 Optimizer 來說，noexcept 是一個有價值的資訊
3. 即使 function 還是內可能拋出 exception，依然可以宣告 noexcept。這種情況表示: 該 function 並沒有對 exception 做任何控制，程式沒有能力應對 exception。因此會直接呼叫 `std::terminate`。
4. 最後，這可以增加可讀性，使 reader 明白 implemter 的意圖。
[[永遠不該扔例外的 function]]

### 傾向於 Pure function
F.8 Prefer pure functions 
- 給予相同的輸入，必然得到相同的輸出。
- 如果結果 depends on `time`, `random`, 就會是 non-pure function

### 如何決定變數傳入與傳出 function 的型態
F.15 [[Prefer simple and conventional ways of passing information]] 
這是一條很大的 rule，後面有很多小條的逐一說明每一種情況。
- F.16 For “in” parameters, pass cheaply-copied types by value and others by reference to const 
- F.19 For “forward” parameters, pass by TP&& and only std::forward the parameter 
- F.17 For “in-out” parameters, pass by reference to non-const 
- F.20 For “out” output values, prefer return values to output parameters 
- F.21 To return multiple “out” values, prefer returning a struct or tuple 
- F.42 Return a T* to indicate a position (only) 
- F.44 Return a T& when copy is undesirable and “returning no object” isn’t needed 
- F.45 Don’t return a T&& 
- F.48 Don’t return std::move(local) 
- F.46 int is the return type for main() 
1. Input parameter: 只有在 copy 很便宜時 pass by copy 
2. 

[[Lambda]]
- F.50 Use a lambda when a function won’t do (to capture local variables, or to write a local function) 
- F.52 Prefer capturing by reference in lambdas that will be used locally, including passed to algorithms 
- F.53 Avoid capturing by reference in lambdas that will be used nonlocally, including returned, stored on the heap, or passed to another thread 

F.51 Where there is a choice, prefer default arguments over overloading
- 如果可以透過設 default variable 取代 overloading，就不要做 overloading. 
```cpp
// Better!
void print(const string& s, format f = {});

// Avoid this!
void print(const string& s);
void print(const string& s, format f);
```

F.55 [[Don’t use va_arg arguments]]

## Ch5 Classes & Class Hierarchies

### 把相關的資料包成 struct 或 class 
- C.1 Organize related data into structures (structs or classes) 
```cpp
void draw(int fromX, fromY, int toX, int toY);
// better
void draw(Point from, Point to);
```
### 使用 Struct 或 Class 的判斷標準
- [[必須使用 Class 而非 Struct 的情況]] 
	1. 會切分實作與介面
	2. 有 member data 需要透過 constructor 生成
- C.2 Use class if the class has an invariant; use struct if the data members can vary independently 
- C.3 Represent the distinction between an interface and an implementation using a class 

### Other 

C.4 Make a function a member only if it needs direct access to the representation of a class 
C.5 Place helper functions in the same namespace as the class they support 
C.7 Don’t define a class or enum and declare a variable of its type in the same statement 
C.8 Use class rather than struct if any member is non-public 
C.9 Minimize exposure of members 
C.10 Prefer concrete types over class hierarchies
C.11 Make concrete types regular 
C.20 If you can avoid defining any default operations, do 
C.21 If you define or =delete any default operation, define or =delete them all C.22 Make default operations consistent 
C.41 A constructor should create a fully initialized object 
C.42 If a constructor cannot construct a valid object, throw an exception 
C.43 Ensure that a copyable (value type) class has a default constructor 
C.45 Don’t define a default constructor that only initializes data members; use member initializers instead 
C.46 By default, declare single-argument constructors explicit 
C.47 Define and initialize member variables in the order of member declaration 
C.48 Prefer in-class initializers to member initializers in constructors for constant initializers 
C.49 Prefer initialization to assignment in constructors 
C.51 Use delegating constructors to represent common actions for all constructors of a class 
C.52 Use inheriting constructors to import constructors into a derived class that does not need further explicit initialization 
C.67 A polymorphic class should suppress copying 
C.30 Define a destructor if a class needs an explicit action at object destruction C.31 All resources acquired by a class must be released by the class’s destructor 
C.32 If a class has a raw pointer (T*) or reference (T&), consider whether it might be owning 
C.33 If a class has an owning pointer member, define a destructor C.35 A base class destructor should be either public and virtual, or protected and non-virtual 
C.80 Use =default if you have to be explicit about using the default semantics C.81 Use =delete when you want to disable default behavior (without wanting an alternative) 
C.82 Don’t call virtual functions in constructors and destructors
C.86 Make == symmetric with respect to operand types and noexcept 
C.87 Beware of == on base classes 
C.120 Use class hierarchies to represent concepts with inherent hierarchical structure (only) 
C.121 If a base class is used as an interface, make it an abstract class 
C.122 Use abstract classes as interfaces when complete separation of interface and implementation is needed 
C.126 An abstract class typically doesn’t need a constructor 
C.128 Virtual functions should specify exactly one of virtual, override, or final 
C.130 For making deep copies of polymorphic classes prefer a virtual clone function instead of copy construction/assignment 
C.132 Don’t make a function virtual without reason 
C.131 Avoid trivial getters and setters 
C.133 Avoid protected data 
C.134 Ensure all non-const data members have the same access level 
C.129 When designing a class hierarchy, distinguish between implementation inheritance and interface inheritance 
C.135 Use multiple inheritance to represent multiple distinct interfaces 
C.138 Create an overload set for a derived class and its bases with using
C.140 Do not provide different default arguments for a virtual function and an overrider 
C.146 Use dynamic_cast where class hierarchy navigation is unavoidable 
C.147 Use dynamic_cast to a reference type when failure to find the required class is considered an error 
C.148 Use dynamic_cast to a pointer type when failure to find the required class is considered a valid alternative 
C.152 Never assign a pointer to an array of derived class objects to a pointer to its base 
C.167 Use an operator for an operation with its conventional meaning 
C.161 Use nonmember functions for symmetric operators 
C.164 Avoid implicit conversion operators 
C.162 Overload operations that are roughly equivalent
C.163 Overload only for operations that are roughly equivalent 
C.168 Define overloaded operators in the namespace of their operands 
C.180 Use unions to save memory 
C.181 Avoid “naked” unions 
C.182 Use anonymous unions to implement tagged unions 

## Ch6 Enum 
Enum.1 Prefer enumerations over macros 
Enum.2 Use enumerations to represent sets of related named constants 
Enum.3 Prefer enum classes over “plain” enums 
Enum.5 Don’t use ALL_CAPS for enumerators 
Enum.6 Avoid unnamed enumerations 
Enum.7 Specify the underlying type of an enumeration only when necessary 
Enum.8 Specify enumerator values only when necessary

## Ch7 Resource Management
R.1 Manage resources automatically using resource handles and RAII (Resource Acquisition Is Initialization) 
R.3 A raw pointer (a T*) is non-owning 
R.4 A raw reference (a T&) is non-owning 
R.5 Prefer scoped objects, don’t heap-allocate unnecessarily 
R.10 Avoid malloc() and free() 
R.11 Avoid calling new and delete explicitly 
R.12 Immediately give the result of an explicit resource allocation to a manager object 
R.13 Perform at most one explicit resource allocation in a single expression statement 
R.20 Use unique_ptr or shared_ptr to represent ownership 
R.21 Prefer unique_ptr over shared_ptr unless you need to share ownership 
R.22 Use make_shared() to make shared_ptrs 
R.23 Use make_unique() to make unique_ptrs 
R.24 Use std::weak_ptr to break cycles of shared_ptrs 
R.30 Take smart pointers as parameters only to explicitly express lifetime semantics 
R.37 Do not pass a pointer or reference obtained from an aliased smart pointer 

## Ch8 Expression & Statement
ES.1 Prefer the standard library to other libraries and to “handcrafted code” ES.2 Prefer suitable abstractions to direct use of language features 
ES.5 Keep scopes small 
ES.6 Declare names in for-statement initializers and conditions to limit scope 
ES.7 Keep common and local names short, and keep uncommon and nonlocal names longer 
ES.8 Avoid similar-looking names 
ES.9 Avoid ALL_CAPS names 
ES.10 Declare one name (only) per declaration 
ES.11 Use auto to avoid redundant repetition of type names 
ES.12 Do not reuse names in nested scopes
ES.20 Always initialize an object 
ES.21 Don’t introduce a variable (or constant) before you need to use it 
ES.22 Don’t declare a variable until you have a value to initialize it with 
ES.23 Prefer the {}-initializer syntax 
ES.26 Don’t use a variable for two unrelated purposes 
ES.28 Use lambdas for complex initialization, especially of const variables 
ES.40 Avoid complicated expressions 
ES.41 If in doubt about operator precedence, parenthesize 
ES.42 Keep use of pointers simple and straightforward 
ES.45 Avoid “magic constants”; use symbolic constants 
ES.55 Avoid the need for range checking 
ES.47 Use nullptr rather than 0 or NULL 
ES.61 Delete arrays using delete[] and non-arrays using delete 
ES.65 Don’t dereference an invalid pointer 
ES.43 Avoid expressions with undefined order of evaluation 
ES.44 Don’t depend on order of evaluation of function arguments
ES.48 Avoid casts 
ES.49 If you must use a cast, use a named cast 
ES.50 Don’t cast away const 
ES.78 Don’t rely on implicit fallthrough in switch statements ES.79 Use default to handle common cases (only) 
ES.100 Don’t mix signed and unsigned arithmetic ES.101 Use unsigned types for bit manipulation 
ES.102 Use signed types for arithmetic 
ES.106 Don’t try to avoid negative values by using unsigned 
ES.103 Don’t overflow ES.104 Don’t underflow 
ES.105 Don’t divide by zero 

## Ch9. Performance 

Per.7 Design to enable optimization 
Per.10 Rely on the static type system Per.11 Move computation from run time to compile-time 
Per.19 Access memory predictably

## Ch10. Concurrency
> Skip first 

CP.1 Assume that your code will run as part of a multi-threaded program CP.2 Avoid data races CP.3 Minimize explicit sharing of writable data CP.4 Think in terms of tasks, rather than threads CP.8 Don’t try to use volatile for synchronization CP.9 Whenever feasible use tools to validate your concurrent code CP.20 Use RAII, never plain lock()/unlock() CP.21 Use std::lock() or std::scoped_lock to acquire multiple mutexes CP.22 Never call unknown code while holding a lock (e.g., a callback) CP.23 Think of a joining thread as a scoped container CP.24 Think of a thread as a global container CP.25 Prefer std::jthread over std::thread CP.26 Don’t detach() a thread CP.42 Don’t wait without a condition CP.31 Pass small amounts of data between threads by value, rather than by reference or pointer CP.32 To share ownership between unrelated threads use shared_ptr CP.40 Minimize context switching CP.41 Minimize thread creation and destruction CP.43 Minimize time spent in a critical section CP.44 Remember to name your lock_guards and unique_locks CP.100 Don’t use lock-free programming unless you absolutely have to CP.101 Distrust your hardware/compiler combination CP.102 Carefully study the literature

## Ch11. Error Handling 
## Ch12. Constants and Immutability 
## Ch13. Templates and Generic Programming 
## Ch14. C-Style Programming 
## Ch15. Source Files 
## Ch16. The Standard Library




----

## 直接在程式碼解釋要做什麼
舉例而言，比起寫一個 for loop 在一個 list 中找到指定的數值，不如使用 `std::find`。
有句諺語是 「如果你使用 explicit loops，代表 你不知道 STL 的 [Algorithms library](https://en.cppreference.com/w/cpp/algorithm)

> A professional C++ developer should know the algorithms of the STL. By using them, you avoid the usage of explicit loops, and your code becomes easier to understand, easier to maintain, and therefore, less error prone. There is a proverb in modern C++: “When you use explicit loops, you don’t know the algorithms of the STL




## What I can do 
- [Algorithms library](https://en.cppreference.com/w/cpp/algorithm)
- 
