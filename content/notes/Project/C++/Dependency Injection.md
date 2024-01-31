---
title: Dependency Injection
date: 2023-12-20 23:03
tags:
  - cpp
---
相依注入(Dependency Injection, DI)
[Types of dependency injection](https://en.wikipedia.org/wiki/Dependency_injection#Types_of_dependency_injection) 有多種，
- Constructor injection
- Setter injection
- Interface injection
總之就是: 如果我需要 "A"，呼叫取得 A 的 function (或產生 A ) 會有某些巨大的代價，像是必須被迫呼叫 singleton 之類的。相依注入就是在外面取得這個結果，然後透過 constructor 或 setter 把這個相依 "注入" 到 Client 的 Argument 當中。

因為沒在 Client 中 hard-coded 呼叫到那個有巨大代價的東西，不直接相依於它，重構上會變得容易。

上網查 Interface injection 比較容易得到 design pattern 的結果，但 DI 應該不限於 Interface Injection。

```cpp
//  Without dependency injection
public class Client {

    Client() {
		int val = Singleton::instance().get_val(); //dependency is hard-coded, inside Client.
		std::cout<< val << std::endl;
    }
}

public class Client {
    Client(int val) { // dependency is in the constructor argument. singleton can be called in outer.
		std::cout<< val << std::endl;
    }
}

//  With dependency injection


```




## Interface Injection
透過介面把 Client 與 Service 之間的依賴性鬆綁，Client 變得依賴於介面，而 Service 則是繼承介面之後的實作。

Dependency injection is used to make a class independent of its dependencies or to create a loosely coupled program. Dependency injection is useful for improving the reusability of code. Likewise, by [decoupling](https://www.techtarget.com/whatis/definition/decoupled-architecture) the usage of an object, more dependencies can be replaced without needing to change class.