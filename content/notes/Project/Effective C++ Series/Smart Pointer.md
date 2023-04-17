在[[為多型用途的基礎類別宣告 virtual 解構式]]文章中的 `TimeKeeper` 例子，我們提及了工廠函式 (factory function)，在該例子，我們把 delete `new` resource 的責任交給 Client。

然而有很多情況--例如 main flow 中過早的 return，resource 可能沒有成功被銷毀。善用 Pointer-like 物件，並把銷毀資源的操作**確實**的寫在 Destructor 中可以避免這些問題。

Smart Pointer 的原理是利用一個 object 去 own (or manage, 管理) 一個 heap-based 的資源，當 Smart Pointer Object 脫離 Scope，Compiler 試圖去 destructor 時，藉機呼叫手上 Object 的 destructor。