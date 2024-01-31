---
title: "關鍵字 typename 在 Template 中的意涵"
date: 2023-05-26 00:56
tags:
- cpp
---
試想，下例中使用 `class` 跟 `typname` 之間有甚麼區別?
```c++
template<class T> class Widget; // uses “class”
template<typename T> class Widget; // uses “typename”
```
答案是意義完全相同，在宣告 template 參數時，這兩個 keywords 並沒有差別，但 `class` 與 `typename` 並不是總是等價。


## 指涉 (refer to)

- 從屬名稱 (dependent names): 在 template 當中的某個**名稱**相依於 template 參數。
- 巢狀從屬名稱 (nested dependent names): 當從屬名稱在 template 內並且是 nested 的。(ex. `T::member_data`)
- 巢狀從屬型別名稱 (nested dependent type names): 是巢狀從屬名稱，且這個名稱代表一個**型別** (Type)。(ex. `T::`)
- 非從屬名稱 (non-dependent names): 類別與 template 參數沒有相依性。

## 區分「巢狀從屬型別名稱」與「巢狀從屬名稱」
巢狀從屬型別名稱會造成 parsing 困難，以下例來說，在不知道 `C` 是什麼之前，要如何解讀 `C::const_iterator * x;`?
1. `C::const_iterator` 可能是一個 member data? 而 `x` 可能是一個 global int variable !
2. `C` 是一個 STL container，則 `const_iterator` 是一個 nested type name.
隨著解讀的方式不同，`*` 符號也有不同的意思。
1. 表示乘法
2. 表示 Type Pointer

這就是 Compiler 遇到的的困境。

```c++
template<typename C>
void print2nd(const C& container)
{ 
	C::const_iterator * x;
	C::const_iterator y;
}
```

## Typename 必須做為 Nested Dependent Type Name 的前導詞
在上述的困境 (nested dependent name OR nested dependent *type* name ) 裡，Compiler 預設行為是 **假設 C 並非一個型別**，除非以 `typename` 明確告訴它這是型別。
按照這個規則再看一次上例，由於沒有 typename 明確指涉 C::const_iterator 是 type name，compiler 認為這代表一個 member data，那 `y` 是什麼? 以空白相隔? 這違反語法，會直接引發錯誤。

作法如下，直接在想要指涉的 nested dependent type name 前面加上關鍵字 `typename` 即可，在 signature 或是直接寫在 function body 內都可以使用這個 keyword。甚至與 `typedef` 結合也沒問題，[[typedef and using]]

```c++
template<typename C>
void f(const C& container, typename C::const_iterator* x);


template<typename C>
void print2nd(const C& container)
{ 
	typename C::const_iterator y = container.begin();
	typedef typename C::const_iterator citor;
}
```

`typename` 除了用在 template 參數，就只允許被使用於**指涉 nested dependent type name**，非 nested 的不能加。
```c++
template<typename C> // OK, 等價於 `class`
void f( const C& container, // non-nested name 不能以 typename 指涉
		typename C::iterator iter); // nested name 必須以 typename 明確指涉，否則編譯會有問題
```

## Typename 不得用在 Base Classes List 與 Member Initializer List 

- Base Class List: 繼承時候冒號後面那一串，不能、也不需要用 `typename` 標示 (能放在這裡就已經是 type 了)
- Member Initializer List 也不需要
除了上述的兩個例外，其他地方照樣能用 `typedef`

```c++
template<typename T>
class Derived: public Base<T>::Nested { // base class list: typename not allowed
public:
explicit Derived(int x): 
	Base<T>::Nested(x)  // base class identifier: 
						// in member initializer list typename not allowed
{
	typename Base<T>::Nested temp;  // use of nested dependent type
									// name not in a base class list or
} // as a base class identifier in a mem. init. list: typename required
};
```

> [!todo]
> 實驗 mem init list 為何不用?



