在[[為多型用途的基礎類別宣告 virtual 解構式]]文章中的 `TimeKeeper` 例子，我們提及了工廠函式 (factory function)，在該例子，我們把 delete `new` resource 的責任交給 Client。

然而有很多情況--例如 main flow 中過早的 return，resource 可能沒有成功被銷毀。善用 Pointer-like 物件，並把銷毀資源的操作**確實**的寫在 Destructor 中可以避免這些問題。

Smart Pointer 的原理是利用一個 object 去 own (or manage, 管理) 一個 heap-based 的資源，當 Smart Pointer Object 脫離 Scope，Compiler 試圖去 destructor 時，藉機呼叫手上 Object 的 destructor。

## Smart Pointer 當中的顯式與隱式轉換
1. Smart Pointer 的 `get` function 是一種顯式轉換 (explicit)，允許 client 取得原始物件的原始型別指標。
2. Smart Pointer Override 了 `operation*` 和 `operator->`，因此 client 端可以直接對它做指標操作，有如對待 raw pointer，這隱含的是隱式轉換 (implicit)

## 顯式/隱式轉換介面
如上述， `get` function 是一種顯式轉換 (explicit)，它的優點是使用時意圖清楚，缺點是很醜。
其實，亦可以提供個隱式轉換的介面，如此當這個物件被放到 base resource 的類別時，就不用特別透過 `get` 提取 base resource，缺點是會提升發生錯誤的風險。

選擇何種，取決於使用情境，記住 [[讓介面容易被使用]]，不要讓你的介面容易被誤用，即可。