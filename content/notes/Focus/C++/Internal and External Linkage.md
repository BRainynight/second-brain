---
title: Internal and External Linkage
date: 2023-09-18 23:31
tags:
  - empty
---
https://learn.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=msvc-170

## External vs. internal linkage

A _free function_ is a function that is defined at global or namespace scope. Non-const global variables and free functions by default have _external linkage_; they're visible from any translation unit in the program. No other global object can have that name. A symbol with _internal linkage_ or _no linkage_ is visible only within the translation unit in which it's declared. When a name has internal linkage, the same name may exist in another translation unit. Variables declared within class definitions or function bodies have no linkage.

You can force a global name to have internal linkage by explicitly declaring it as **`static`**. This keyword limits its visibility to the same translation unit in which it's declared. In this context, **`static`** means something different than when applied to local variables.

The following objects have internal linkage by default:

- **`const`** objects
- **`constexpr`** objects
- **`typedef`** objects
- **`static`** objects in namespace scope

To give a **`const`** object external linkage, declare it as **`extern`** and assign it a value:

[[External Linkage]]