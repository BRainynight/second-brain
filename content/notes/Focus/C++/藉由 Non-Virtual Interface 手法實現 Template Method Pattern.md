---
title: "藉由 Non-Virtual Interface 手法實現 Template Method Pattern"
date: 2023-05-14 15:16
tags:
- cpp
---
> The Template Method Pattern via the Non-Virtual Interface Idiom

這個方法是 Design Pattern [[Template Method]] 的表現形式，而跟 C++ Template 無關。

## Non-Virtual Interface (NVI)
NVI 主張 Virtual 應為 Private (Private virtual function)，如果有暴露的需求，則應該以一個 Public non-virtual function (as a *wrapper*) 呼叫 Private virtual function。

## wrapper function
Wrapper 的優點可以把一些呼叫 virtual 前後需要處理的事情藏起來，確保這些事情必定會執行: 
例如
- 在呼叫 virtual function 前: 為 Mutex 上鎖, Log entry, 驗證事前條件...
- 在呼叫 virtual function 之後: 為 Mutex 解鎖, 驗證事後條件...

如果把 Virtual 設成 Public (相當允許客戶端自行重新定義它)，這些事件將無處置放，也無法確保事前事後條件絕對會被執行 (Client 端實作時可能會忽略)。

## 保留何時呼叫 virtual function 的權利
NVI 手法把「如何實現機能 (重新定義函式)」的權利交給了客戶端，「何時呼叫函式 (when to call non-virtual function)」的權利留在手上。

## NVI 允許 Protected
某些時候，Derived Class 會需要呼叫 Base Class 的 function，當這個 function 正是前面所說 NVI 的主角 -- 是一個 virtual function 的時候，它必須得宣告成 protected，這在 NVI 中也是被允許的。

某些時候，virtual function 必須是 Public (ex. 多型用途的 Base Class 解構式, [[不要為非多型用途的 Base Class 宣告 Virtual Function]]) 他們則不是用於 NVI 手法。
