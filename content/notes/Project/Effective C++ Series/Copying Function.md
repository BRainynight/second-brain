---
title: "Copying Function"
date: 2023-04-17 00:05
tags:
- cpp
---

> Effective C++ 中，Copying Function 指的是 Copy construcot & Copy Assignment

1. 當 Programmer 自己定義 Copying function 時，Compiler 不會警告你出錯!
2. 在繼承的架構中
	1. 不只屬於 Child Class 的 member data 要全部 copy
	2. 還要記得 call Parent Class 的 copying function。

	```cpp
// Copy Construcotr 
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
: Customer(rhs), // invoke base class copy ctor
priority(rhs.priority)
{
	logCall("PriorityCustomer copy constructor");
}

// Copy Assignment
PriorityCustomer&
PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs); // assign base class parts
	priority = rhs.priority;
	return *this;
}

	```
3. Copy Constructor 與 Copy Assignment 不應該 Call 彼此，如果有 Reusable Code，應該另外抽一個 private function 去共用。