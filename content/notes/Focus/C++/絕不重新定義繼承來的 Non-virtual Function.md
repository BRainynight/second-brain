---
title: "絕不重新定義繼承來的 Non-virtual Function"
date: 2023-05-17 23:48
tags:
- cpp
---
![[Item36.png]]
試想圖中這個繼承關係，`D` 繼承 `B`。而下面這段 code 分別以 `B` pointer 和 `D` pointer 持有 `x` 物件後呼叫 `mf` 方法。你會預期，這兩者的結果會相同，因為他們指向同一個物件。
```cpp
D x; // x is an object of type D

B *pB = &x; // get pointer to x
pB->mf(); // call mf through pointer

D *pD = &x; // get pointer to x
pD->mf(); // call mf through pointer
```

事實卻是，當 `D` 繼承 `B` 後如果自行實作了 `mf`，在以上這段例子中，`x` 會因為被 `B*` 或 `D*` 持有，而有不同的表現!! 當 `D` 有如此實作時，相當於藏住了 `B::mf`。參見 [[繼承時的名稱遮掩行為]]
```cpp
class D: public B {
public:
	void mf();
...
};
```

造成這個現象的原因，參見 [[靜態綁定 (statically bound) 與動態綁定 (dynamically bound)]]

## 絕對遵守 Is-A 關係
本條款其實是 [[確保 Derived Class 和 Base Class 之間必然保持 Is-a 關係]] 的延伸，在
[[區分介面繼承(interface)和實作繼承(implement)]] 說到 non-virtual 代表不變性，綜合此二條規定檢視這個繼承關係
1. 適用 Base Class 的每件事都適用於 Derived Class。
2. 對於 Non-virtual function，Derived Class 應該繼承**介面與實作**

一旦 `D::mf` 重新定義，就違反了 Is-A 關係，特異性凌駕了不變性。