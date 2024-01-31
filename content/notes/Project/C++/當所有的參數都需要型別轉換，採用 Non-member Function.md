---
title: "當所有的參數都需要型別轉換，採用 Non-member Function"
date: 2023-04-22 20:47
tags:
- cpp
---

讓 Class 支援隱式轉換通常不是好事 -- 但也有例外，最常見的就是數值型別。書中以有理數 `Rational` 為例，他設計了一個允許 Int 隱式轉換成 Rational 的 Constructor。
```cpp
class Rational {
    public:
        Rational(int numerator=0, int denominator=1); 
        // 允許 int-to-Rational 的隱式轉換

        int numerator(); // 分子
        int denominator(); // 分母
        const Rational operator*(const Rational rhs) const;
}
```

當實作乘法運算時，若兩個數字都是有理數沒有問題。與 Int 相乘，Int 在前項卻出了問題。
```cpp
Rational oneEight(1, 8);
Rational oneHalf(1, 2);

Rational res = oneEight*oneHalf; // OK
res = res*oneEight; // OK

# eq3
res = oneHalf*2; // OK: oneHalf.operator*(2)
# eq4
res = 2*oneHalf; // Error: 2.operator*(oneHalf)
```
在 eq4 會錯誤是因為，乘法隱含的是
1. 尋找 `2` 的 `operator*`，但這不存在 (2 沒有對應的 class)
2. Compiler 嘗試尋找 Namespace 下或 global scrope 下， Signature 能相配合的 `operator*`，也就是嘗試 `res = operator*(2, oneHalf)` 能否成立。但這也找不到而
3. 沒招了，引發 error。

而 eq3 能成功是因為 Compiler 嘗試先呼叫 `oneHalf.operator*`，2 在傳進去時會因為 Rational 接受隱式轉換 (implicit type conversion)，而若 constructor 限定要 explicit type conversion，甚至會連 eq3 都不過! 

## 原因: 只有列於參數列 (Parameter List) 才能參與隱式轉換

綜合 eq3, eq4 所述，只有當 `int` 列在 `Rational` 物件後面，也就是成為 `Rational::operator*`  的 Parameter List，才是隱式轉換的合格參與者。

## 解法:以 Non-member Function 定義 operator*
只要將 `operator*` 拆離 class `Rational`，讓 operator 的兩個參數 `lhs` & `rhs` 都有參與隱式轉換的資格，那麼 eq3 和 eq4 就都可以通過了!
甚至，這個 non-member function 也不需要定義為 friend，因為光透過 Rational 的 Public interface 就可滿足一切需求了! 
[[operator overloading]]

```cpp

class Rational {
    ...
};

const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator()*rhs.numerator(), \
					lhs.denominator()*rhs.denominator());
}
```
	
