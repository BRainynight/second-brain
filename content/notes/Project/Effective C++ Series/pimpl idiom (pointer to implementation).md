---
title: "pimpl idiom (pointer to implementation)"
date: 2023-05-06 15:07
tags:
- cpp
---
> 將物件的實作細目隱藏在一個指標背後

## 第一種手法: Handle Class

此手法會把一個類別分成兩個 Class: 
- 一個是暴露給客戶端的接口 Handle Class (ex. `Person`)，它只會擁有一個 pointer 指向實作 class
- 一個是實作類別 Implementation Class (ex. `Personimpl`) ，所有真正要存的資料都在這裡面。

由於接口 `Person` 只 own 一個 smart pointer ，它不需要知道 `PersonImpl` 有多大，因此可以用 forward declare 解決。它還提供了一些 getter，但提供 getter 也都可以透過 forward declare 解決一切。

客戶端在 `include person.hpp` 時，只會跟著 include 到 string 和 memory 兩個 header file 而已。至此，`PersonImpl` 做了什麼更動，直接跟客戶端脫鉤。


```cpp
#include <string> // standard library components shouldn’t be forward-declared
#include <memory> // for tr1::shared_ptr; see below
class PersonImpl; // forward decl of Person impl. class
class Date; // forward decls of classes used in
class Address; // Person interface
class Person {
public:
	Person(const std::string& name, const Date& birthday,
	const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	...
private: // ptr to implementation;
	std::tr1::shared_ptr<PersonImpl> pImpl; // 這是唯一的 member data
}; // std::tr1::shared_ptr
```

[[編譯依存-宣告式、定義式與實作細節]]

### 實作檔案 (CPP)
實作檔案需要同時 include `Person.hpp` 和 `PersonImpl.hpp`
-  `Person.hpp` : 為了實作 `Person`的 function
-  `PersonImpl.hpp`: 才能 Call `PersonImpl` 的 function。

```cpp
#include "Person.h" 
#include "PersonImpl.h" 
Person::Person(const std::string& name, const Date& birthday,
const Address& addr)
: pImpl(new PersonImpl(name, birthday, addr))
{}
std::string Person::name() const
{
return pImpl->name();
}
```


## 第二種手法: Interface Class 的設計方式
暴露給客戶的是 Interface Class，這個類別本身會設計成一個 abstract base class (interface class)。[[區分介面繼承(interface)和實作繼承(implement)]]

### Interface Class: 暴露給 Client 的接口
Interface class 的用途是僅有敘述 drived class 的介面，它沒有 member data、也沒有 constructor，只有一個 virtual destructor，跟一堆 [[Pure Virtual Function]] 來敘述介面。而 drived class 就是它的實作 (相當於前面 implement class 的腳色)
```cpp
class Person {
public:
	virtual ~Person();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
	virtual std::string address() const = 0;
...
};
```

我們暴露給 Client 端的是 Interface class，Interface calss 是 abstract class，然而， **abstract class 不能被具象化**。因此，用此方法設計時，需要在  interface class 裡面提供一個「讓 client 端獲取物件」的特殊方法。

這個特殊方法通常稱為 [[工廠函式 (Factory Function)]]，它們會回傳一個 interface class pointer，卻指向動態配置(被 `new` 出來) 的 derived class 物件。這種函式在 interface class 內往往宣告為 `static`。如下例的 `create`: 

```cpp
class Person {
public:
...
static std::tr1::shared_ptr<Person> 
create(const std::string& name, // Person initialized with the
		const Date& birthday, // given params; see Item 18 for
		const Address& addr); // why a tr1::shared_ptr is returned ...
};
```

### Concrete Class: 相對於 Interface Class 的對應實作
Interface Class 所對應的實作類別會是一個具象類 (concrete class)，它必須擁有真正的 constructor。假設這個實作類別是 `RealPerson`: 

```cpp
class RealPerson: public Person {
public:
	RealPerson(const std::string& name, const Date& birthday,
	const Address& addr)
	: theName(name), theBirthDate(birthday), theAddress(addr)
	{}
	virtual ~RealPerson() {}
	std::string name() const; // implementations of these 
	std::string birthDate() const; // functions are not shown, but 
	std::string address() const; // they are easy to imagine
private:
	std::string theName;
	Date theBirthDate;
	Address theAddress;
};
```

現在知道 `RealPerson` 的 constructor 長相，回頭 `Person::create` 的實作也是輕而易舉: 
```cpp
std::tr1::shared_ptr<Person> Person::create(const std::string& name,
const Date& birthday, const Address& addr)
{
	return std::tr1::shared_ptr<Person>( 
			new RealPerson( name, birthday, addr));
}
```

## pimpl 手法的成本
以上說明了兩種花俏的手法，它能降低耦合，減少編譯時間。成本呢?

### Handle Class 的成本
1. 每次對 Handle class 取值都是間接取值: handle class 需要跟 impl pointer 取得資料。
2. 與不用 pimpl pattern 手法想比 (不去耦合)，每增加一個 handle class 物件，就會增加一個 impl pointer 的大小 (通常以 smart pointer 存)。
3. impl object 是以動態記憶體配置 (`new`)，承受動態記憶體配置與釋放的成本，也有可能遇到 `bad_alloc` (記憶體不足)。
### Interface Class 的成本
1. Interface Class 每個函式都是 virtual function，每次的函式呼叫都要付出間接跳躍 (indirect jump) 的成本。見: [[為多型用途的基礎類別宣告 virtual 解構式]]
2. 只要有 virtual function，就會有 vptr (virtual table pointer)，其成本參見:  [[不要為非多型用途的 Base Class 宣告 Virtual Function]]

### 提醒
不論 handle class 或 interface class，一旦脫離 inline 函式都無法有太大的作為(why? 不過就是都要在 class 定義式中直接把實作寫完的意思)。因為這類 class 是為了隱藏實作細節或函式本體的!! [[了解 Inline 的裡裡外外#向 Compiler 發出申請]]


## 該使用 pimpl 嗎?
- 當以上提及的速度成本或大小問題，使得類別的耦合問題相形之下不怎麼嚴重時，就應該直接用具象類別 (concrete class) 取代 pimpl 手法。
