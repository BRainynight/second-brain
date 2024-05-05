---
title: "Template Specialization"
date: 2023-04-23 11:50
tags:
- cpp
---

Template 可以針對特定的 Type 特化，寫法如下
1. `template<>` 裡面不放任何參數，表示這不是 template 也不是標準的 class，是一個特化的 `MsgSender`。
2. `class MsgSender<CompanyZ>` 表示  template `MsgSender` 在遇到 input type 是 `CompanyZ` 的時候，要用以下定義的內容。
以下這段範例就是 `MsgSender` 針對 `CompanyZ` 特別訂製的內容，這就是模板全特化 (Total Template Specialization)。

```c++
template<> // a total specialization of
class MsgSender<CompanyZ> { // MsgSender; the same as the
public: // general template, except sendClear is omitted
void sendSecret(const MsgInfo& info)
{ ... }
};
```
此例呼應 [[了解如何在 Template 中指涉 Base Class 成員]] 的範例，`MsgSender` 對於一般輸入類別都有 `sendSecret` 跟 `sendClear` 兩個 function。但在這裡，`CompanyZ` 的特化版將不存在 `sendClear`! 


## Related Content

[[透過關鍵字 inline 解決 Template Specilization 中的 Multiple Definition]]
