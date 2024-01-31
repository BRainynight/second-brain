---
title: "確保 Derived Class 和 Base Class 之間必然保持 Is-a 關係"
date: 2023-05-11 20:07
tags:
- cpp
---

"Is A" 關係，代表是用於 Base Class 的每一件事，**必定**也是用在 Derived Class，因為每一個 Derived Class 都 "Is A" Base Class。

物件導向上的關係可能跟真實世界的理解有所不同，
例如: 企鵝是一種鳥，若 
- Base Class 為 Bird、Bird 裡面有個 function `fly`。
- Derived Class 為 Penguin，Penguin 繼承 Bird，但企鵝不會飛!! 
這就不是一個適當的繼承， `fly` 並不能適用在 Derived Class Penguin。

又比如，Rectangle 與 Square，Square 繼承 Rectangle，Square 有長寬必定相等的強烈保證。但在以下 function 中，傳入 `Square` 物件時，Assert 一定會發生!
```cpp
void makeBigger(Rectangle& r) // function to increase r’s area
{
	int oldHeight = r.height();
	r.setWidth(r.width() + 10); // add 10 to r’s width
	assert(r.height() == oldHeight); // assert that r’s
}
```

這就代表，在物件導向的視角，Rectangle 的每一件事並不能完全套用在 Square 上，這個繼承關係是有問題的。

查覺到不適合以 Is A 關係塑模，可以考慮 [[Has A]] 跟 [[Is Implemented in Terms of]]，這些將在 [[確定 Composition 塑造的是 'Has-A'關係 或 '根據某物實作'的關係]]、 [[審慎的使用 Private 繼承]]
