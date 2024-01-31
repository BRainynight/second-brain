---
title: "Template 帶來的程式碼膨脹"
date: 2023-05-27 22:34
tags:
- cpp
---
Template 可能導致 binary 內有重複的程式碼、資料，儘管 source code 看起來沒有重複的問題，object code 卻異常肥大。

## 避免輸入類別無關的 code 帶來的程式膨脹
跟共性與變性分析 (commonality and variability analysis)
把程式碼中與「輸入類別有關」跟「與輸入類別無關」的部分分開。困難的是需要學習「感受」template 被具現化很多次時可能發生的「重複行為」。

下面這段例子，Template 輸入參數有兩個: `T` 跟 `n` (矩陣的 size)，只要這兩個參數的組合不一樣，就會具現化一次物件。
`sm1` 跟 `sm2` 分別是一個 "5\*5 矩陣" 跟 "10\*10矩陣" 物件，並且 `SquareMatrix::invert` 會被具現化**兩次**!! 
```cpp
template<typename T, std::size_t n>
class SquareMatrix { 
public:
	void invert(); 
};

SquareMatrix<double, 5> sm1;
sm1.invert(); // call SquareMatrix<double, 5>::invert
SquareMatrix<double, 10> sm2;
sm2.invert(); // call SquareMatrix<double, 10>::inver
```

解決辦法: 把 `invert` 核心部份抽出來自成一個 Template，另一個 Template 專處理不同的 size。
下面的解決辦法有幾個看點
1. `SquareMatrixBase` 和 `SquareMatrix` 走的是 private 繼承，表示 **不是 is a 關係**。
2. `using SquareMatrixBase<T>::invert` 是為了避免[[繼承時的名稱遮掩行為]]，`SquareMatrixBase::invert` 與 `SquareMatrix::invert` 雖然 signature 不同，卻有名稱遮掩問題。
3. `this->invert(n)`: 
	1. [[了解如何在 Template 中指涉 Base Class 成員]] 中提到的。
	2. 這裡做的是隱晦的inline 呼叫，不會因為呼叫而帶來而外的成本。[[了解 Inline 的裡裡外外]]

這樣一來
- `SquareMatrixBase<double>` 只會有一份
- `SquareMatrix<double, 5>`, `SquareMatrix<double, 10>` 各一份，但他們呼叫到的 `SquareMatrixBase<double>`  會是同一份。
```c++
template<typename T> // size-independent base class for
class SquareMatrixBase { // square matrices
protected:
	void invert(std::size_t matrixSize); // invert matrix of the given size
};

template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T> {
private:
	using SquareMatrixBase<T>::invert; // 因為有同名的 invert (雖然 signature 不同)
public:
	void invert() { this->invert(n); } // make inline call to base class
}; // version of invert
```

## 與輸入類別相關的 code 所帶來的程式膨脹
像是 `std::vector<int>`, `std::vector<double>` 勢必會造成兩個不同的 class。
同樣的 `std::vector<int*>`, `std::vector<double*>` 也會，如果沒有必要生成這麼多的 class，對於 pointer type，讓操作強型別 (Strongly type pointer `T*`) 去呼叫無型別 (`void*`) 是需要的。






