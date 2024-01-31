---
title: "了解如何在 Template 中指涉 Base Class 成員"
date: 2023-05-12 22:09
tags:
- cpp
---

考量以下的類別關係，`Company` classes 會作為 template 的輸入參數傳入 MsgSender 體系的 Template。
`LoggingMsgSender` 在繼承 `MsgSender` 的時候，刻意為新的 function 取 `sendClearMsg` ，不同於 Base class `sendClear`，這是好的做法，避免了 [[繼承時的名稱遮掩行為]] 以及遵守 [[絕不重新定義繼承來的 Non-virtual Function]]。
![[Item43.png]]
以下是 `LoggingMsgSender::sendClearMsg` 的 function body，這段 code 卻**無法通過編譯**

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
	... // ctors, dtor, etc.
	void sendClearMsg(const MsgInfo& info)
	{
		// do some log...
		sendClear(info); // 呼叫繼承來的 base class function
		// do some log...
	}
...
}
```

問題是，當 Compiler 讀到 `class LoggingMsgSender` 的時候，並不知道它繼承的 `MsgSender<Company>` 具象化起來，是怎麼樣的一個 class，Compiler 沒辦法確保這個未知的 Base class 是否有 `sendClear` function。

## Template 繼承規則與物件導向繼承規則不同
這正是條款1所說的，C++ 是一個聯邦。Template C++ 與 Object Oriented C++ 有些概念是不同的只能透過 Template Specialization 可以對特定的類別訂製特定的內容，Template 的繼承規則並不如物件導向繼承規則，在知道 `MsgSender<Company>` 所代表的實體 class 之前，沒辦法確定 sendClear 是從哪來的，因為當前的 LoggingMsgSender 不存在這樣的 function。

## 解決辦法
以下的作法都是權宜之計，都是假設 Base Class 確實擁有 `sendClear` 的情況，但書中有沒有提更好的解法。
### 在 Base Class function 前加上 `this->`
```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info)
	{
		this->sendClear(info); // pass, 假設 sendClear 會被繼承
	}
}
```

### 使用 Using 宣告式
[[使用關鍵字 using 讓特定 function 在 Scope 內可見]]，使用的方法相同。不過在該例中是為了 [[繼承時的名稱遮掩行為]] 問題，本例的肇因卻是 Compiler 不會進入 Base Class Scope 找 function，我們透過 `using` 請 Compiler 這麼做。

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
	using MsgSender<Company>::sendClear;
	void sendClearMsg(const MsgInfo& info)
	{
		sendClear(info);
	}
}
```


### 以 Base Class 的 Namespace 呼叫該 Function
```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info)
	{
		MsgSender<Company>::sendClear(info);
	}
}
```

這個方法的缺點是如果被呼叫的是 virtual function，這個明確的修飾(explicit qualification) (`MsgSender<Company>::`) 會關閉 virtual 的綁定行為。

### 結論
在 invalid reference to base class member 這個問題上，Compiler 有兩種做法
1. 在檢視 Derived Class Template Definition 時就診斷，此處的缺點是 Template 參數尚未具象化，無法得知 "真正的 Base Class" 的長相
2. 等到 Template 參數具象化時，再檢視這個 reference 是否有效。

C++ 的政策是傾向第一種，及早診斷。因此 Compiler 彷彿完全不知道 Base Class 有哪些東西可以呼叫一樣。

而上述的三個手段，就是讓 Compiler 不要看到黑影就開槍(爆 error)，「先」假設 Base Class 有這個 function，讓編譯往下走。如果後來發現因為 template specialization 等原因，呼叫的 function 不存在，依然不會通過編譯，這依然是一個無效的 reference。