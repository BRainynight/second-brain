---
title: Impure Virtual Function
date: 2024-02-23 12:57
tags:
  - cpp
---

```cpp
class Airport { ... }; // represents airports
class Airplane {
public:
	virtual void fly(const Airport& destination);
...
};
void Airplane::fly(const Airport& destination)
{
	// default code for flying an airplane to the given destination
}
class ModelA: public Airplane { ... };
class ModelB: public Airplane { ... };
```

相當於告訴 Client: 你需要提供一個這樣的函式，如果不想自己寫，可以用預設的內容! 

但是，讓 impure virtual function 同時擔任「要求 client 給一個這樣的函式」又在「實作中放了預設行為，相當於假設所有的 Derived Class 都可以接受這個預設行為」可能導致其他問題: Client 端沒有主動說明「我要這個預設行為」。
當 Client 端忽略了有這個 function 要 override，就會導致錯誤 -- 該 Derived 可能無法執行這個預設行為。

## 把預設行為跟提供介面切開
一個好的做法是--斷開兩者的連結。利用 [[Pure Virtual Function]] 提到的做法，把預設的實作寫在 Pure Virtual Function 裡面，當 Derived 想要用預設實作時自己去 call 就好。


```cpp
class Airplane {
public:
	virtual void fly(const Airport& destination) = 0; // 提供介面
}

void Airplane::fly(const Airport& destination)
{ // 為 pure virtual function 提供實作
	default code for flying an airplane to the given destination
}

class ModelA: public Airplane {
public:
virtual void fly(const Airport& destination)
{ Airplane::fly(destination); }
};

class ModelC: public Airplane {
public:
virtual void fly(const Airport& destination);
...
};
void ModelC::fly(const Airport& destination)
{ // ModelC 不用預設的實作，就不要 Call Airplane::fly，自己寫
code for flying a ModelC airplane to the given destination
}
```