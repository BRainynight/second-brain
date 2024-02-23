---
title: How to Pass Output Value
date: 2024-02-21 23:17
tags:
  - cpp
---

> 多數情況下，請 Return Value (by Copy)。

## Single value
直接 return value ，不要以 const value 回傳，因為特地以 const value 回傳並沒有特別的意義。
(Since C++17) 雖然 copy 「看似」昂貴，但 compiler 有 RVO (return value optimization) 或 NRVO (Named returned value optimization)，經過 optimize 後 copy 得以被省略

## Multiple output value : return struct or tuple 

C++ STL 中 `std::set::insert` 的回傳就是一個 `std::pair`，內容存了 iterator 與 bool (是否插入新值)。

至於如何優雅的接收這類(多個)回傳值，建議用 C++11 的 `std::tie` 或 C++17 的 [Structured binding](https://en.cppreference.com/w/cpp/language/structured_binding) 。

### std::tie 
透過 `std::tie`，直接把 `std::pair` 的第一位與第二位分別指派給 `iter` 與 `is_inserted`。
```cpp
std::tie(iter, is_inserted) = mySet.insert(2020); 
```

### Structured Binding

更直覺的用法 unpack 回傳值

```cpp
auto [iter, is_inserted] = mySet.insert(2021);
```

## 例外: Return with pointer 或 lvalue reference 

像後面會提到的，pass by pointer/reference 都**不應**具有轉移所有權的情況發生 (不應，不是辦不到。一旦做了很容易發生所有權混亂，導致 memory leak)。

下列的情況都應該 follow 這個準則: 雖然 return by pointer/reference，但不具有轉移所有權的問題。

### Pointer 只代表 Position: return `T*`

當回傳的內容只代表一個記憶體位置 (tree node, an address in std::list ... )，該資源本身在 function 之外，則可以回傳 pointer。

### 不想要 Copy 發生，且不需要回傳物件的時候 return `T&`

當不需要複製並且不需要「不回傳物件」時傳回 T&

當 "Return no object" 不是選項，則 return by reference，而非 return by pointer。

為了避免一些暫時變數的 copying, destruction，有時會選擇 chain operation。
通常發生在 assignment operator。

```cpp
A& operator = (const A& rhs) { ... };
A operator = (const A& rhs) { ... };

A  a1, a2, a3;
a1 = a2 = a3;
```

兩個 copy assignment 分別多創建了兩個 temporary object。

## 危險動作: return a reference to a local variable

回傳一個 reference/pointer 到 local variable 都會造成 undefined variable，結果無法預期，也不一定總會 crash。

這兩個動作也同樣危險
1. Return `T&&`
2. Return `std::move(local)`

### Return `T&&`
下面這段範例，就意義上 rvalue 在 `auto myInt` 接收完，該行執行完，就已經結束 lifetime 了。GCC Compiler 甚至不會讓這種 code 通過。

```cpp
int&& returnRvalueReference() {
   return int{};
}

int main() {

   auto myInt = returnRvalueReference();
   // lifetime for myInt (rvalue) is END!!!
}

```

### Return `std::move(local)`

由於 Compiler Optimization 在 return value (by copy) 已經推出 RVO, NRVO -- 在優化時直接省略 Copy，`std::move(local)` 反而不是優化的手段，甚至可能更慢。
