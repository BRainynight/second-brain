## CPP Ref
https://en.cppreference.com/w/cpp/language/inline


### Explanation
當 function or variable (C++17) 被宣告為 inline，代表它擁有以下特性 (以下簡稱 inline object)
1. 在每一個 TU (translation unit) 當中，inline object 的定義必須是可存取的 (definition should be reachable -> definition should in hpp)。
2. 如果一個 inline object 被宣告於 hpp，並且此 hpp 被多個 cpp inlcude，表示
	- 此 inline obejct 擁有 [[External Linkage]] (它的名稱在其他 TU 被引用且沒有被宣告 `static`)
	- 它在多個 TU 之間可能擁有多個定義，但在每一個 TU 的定義都是相同的。

儘管具有這些特性，最終是否予以 inline subsititution 卻仍由 compiler 決定。

## Inline 的歷史淵源

Inline 這個關鍵字最初的用意，也是最廣為人知的用意是把 function call 替換成 function body 本身，也就是 [inline substitution](https://en.wikipedia.org/wiki/inline_expansion "enwiki:inline expansion")。其代價是 object file 變大，因為每個 call 到 inline 的地方都會被「貼上」一次，但有優化的作用。

然而，因為是否替換 function call 由 compiler 自由決定，被宣告 inline 的 function 不必然被替換，沒被宣告 inline 也不一定不被替換。這代表 inline function optimization 不在綁定於 keyword `inline`。

需要注意的是，Compiler 選擇 inline optimization 與否，並不會改變有關 multiple definition 的規定。

> Function 最終被 compiler inline 與否，都不應該擁有 multiple definition。

在前面 Explanation 提到，inline function 在多個 TU 當中是擁有多個定義 (multiple definitions) 的，且關鍵字 inline 並不與 inline optimization 綁定。這個關鍵字的意義逐漸從「偏好 inline optimization」轉變成 「允許多重定義」，且這重含意在 C++17 中被延伸到 variable 上面。

## Inline Optimization 的條件

1. Definition is reachable in each TU -> definition should be put in hpp.
	- Subition or not is still decided by compiler.
2. 宣告 inline function 於 hpp，將 definition 放在 cpp
	1. 當有其他 TU include 了該 inline function 所在的 hpp，會引發 warning: inline function used but never defined

## Template Specialization


[[Template Specialization]]
### Notes
## When Does Compiler deciding "don't do subtition" 

The **`inline`** keyword tells the compiler that inline expansion is preferred. However, the compiler can create a separate instance of the function (instantiate) and create standard calling linkages instead of inserting the code inline. Two cases where this behavior can happen are:

- Recursive functions.
    
- Functions that are referred to through a pointer elsewhere in the translation unit.
    

These reasons may interfere with inlining, _as may others_, at the discretion of the compiler; you shouldn't depend on the **`inline`** specifier to cause a function to be inlined.

Rather than expand an inline function defined in a header file, the compiler may create it as a callable function in more than one translation unit. The compiler marks the generated function for the linker to prevent one-definition-rule (ODR) violations.

