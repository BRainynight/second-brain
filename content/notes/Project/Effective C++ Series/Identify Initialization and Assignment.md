---
title: "Identify Initialization and Assignment"
date: 2023-04-10 21:02
tags:
- cpp
---

> C++ 規定，member data initialization 發生在**進入 Constructor 之前**。在 Constructor 賦值屬於 assignment。 正確的 initialization 是使用 member initialization list (成員初值列)，取代賦值 (assignment)。

此例中，第一種的做法效率好: 
- 第一種作法使用  member initialization list 是對 member data 做 Copy Construct。
- 第二種作法 `m_name`會隱含的 call 一次 `std::string` 的 default constructor，再以 Copy assignment 被賦予值

```cpp
class Book {
    private:
        std::string m_name;
    public:
        // good way
        Book(const std::string& name): m_name { // copy construct
        }
        // bad way
        Book(const std::string& name) {
            m_name = name;  // copy assignment
        }
}
```
