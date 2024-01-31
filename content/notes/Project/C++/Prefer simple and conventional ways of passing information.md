---
title: Prefer simple and conventional ways of passing information
date: 2024-01-14 21:41
tags:
  - cpp
---
## 如何決定 Function Signature 的長相

- headings: 資料結構 copying 跟 moving 的成本
- row: parameter 的性質
	- In & retain copy: 在 function 內部會發生 copy 
	- In & retain "copy": Moved-from means that it is in a valid but not nearer specified state.
	- In/out: 在 function 會被變更內容
	- out: 透過 function 所產生的回傳值
後面會有更多 rule 說明這些東西
![[Pasted image 20240114215359.png]]

案例
- 當 Copy 很輕鬆，或不可能發生 Copy 的時候，pass by copy 沒問題: int, std::uniqure_ptr。
- Move 的成本低: `std::vector`, `std::string`
- Move 的成本適中: `std::array<std::vector>` or BigPOD (POD stands for Plain Old Data—that is, a class without constructors, destructors, and virtual member functions.)
- 不知道 Move 的成本: Template。