---
title: "Pass by value 當中的 Copy 行為"
date: 2023-04-17 23:57
tags:
- cpp
---

## Simple Pass By Value
考量下面的程式 `validateStudent(s)` 執行的成本有什麼?

```cpp
class Person;
class Student: public Person;
bool validateStudent(Student s); // pass by value = copy
Student s = Student();
validateStudent(s); 
```

成本是
- Student Copy Constructor
- Person Copy Constructor
一個 Copy Ctor 就意味著一次全部 member data 的 Copy，所以 data 越多呼叫越多 Copy Ctor!! 

## 多型函式
當 Signature 是 Parent，傳入的是 Child，更糟糕的是會發生 Slicing! 只有 `Person` 部分的資料會被 Copy，`Worker` 的資料都被切割了。

```cpp
class Worker: public Person;
bool showName(Person s);

Worker w = Worker();
showName(w);
```