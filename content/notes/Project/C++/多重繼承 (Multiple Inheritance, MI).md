---
title: "多重繼承"
date: 2023-05-23 23:06
tags:
- cpp
---
- 單一繼承 (Single Inheritance, SI)
- 多重繼承 (Multiple Inheritance, MI)
---

## 了解 C++ 如何解決歧異 (ambiguity)

函式名稱、typedef 都可能發生歧異。C++ 解決歧異的方式與決議(resolving) overloading function 的規則相同
- 先找最匹配的呼叫函式
- 如果匹配度相同，才會發生歧異，因為沒有最佳匹配。

面對歧異，在呼叫的時候需要明指呼叫的是哪一個 class 的 function:
```cpp
obj.BaseClass::someFunc();
obj.DerivedClass::someFunc();
```

## 鑽石繼承
試想下圖，假設 `File` 裡面有一個 member data `fileName`，而在 `IOFile` 當中，它該有幾個 `fileName` data?
![[Item40.png]]

1. 來自 `InputFile::fileName`, `OutputFile::fileName`各一份
2. 只該一份，來自兩個 Parent Class 的 fileName 應該要相同，且只有一份 `fileName` 資料握在 `IOFile`。

C++ 的預設做法是 (1)，各複製一份。但同時也支援 (2)，只是在繼承時需要宣告 virtual: [[Virtual Base Class]]。

## 結論
- 有單一繼承，就用單一繼承
- 如果多重繼承能帶來比單一繼承低的維護成本、且合理，別猶豫。
	- 其中一種例子 (P195~199) : public 繼承某個 Interface class, private 繼承某個協作實作的 class，就是多重繼承的一個合理展現。
