---
title: "打破 Constness 限制"
date: 2023-04-10 21:03
tags:
- cpp
---

### Physical Constness
> 編譯器堅守的觀點: Physical Constness，又稱 Bitwise constness。Const member function 不可以修改任何 non-static member data。

然而，請看下例: `operator[]` 確實不會更動到 member data，可以通過 Bitwise Testing，卻把「改動權」暴露給 Client 端，造成不應該的賦值行為。
- [[避免傳回 Handles 指向物件的 Private & Protected Member Data]]

```cpp
class CTextBlock {

public:
    // inappropriate (but bitwise const) declaration of operator[]
    char& operator[](std::size_t position) const
    { return pText[position]; }
    
private:
    char *pText;
}

const CTextBlock ctb("World");
ctb[0]='F'; // Become "Forld"
```
此例應該將回傳型態修改為 `const char&`。

編譯器堅守的 Bitwise constness 觀念，造成 Const Function 作用過於綁手綁腳，甚至在 Const & Non-Const function 之間我們可能需要 Own 兩份相似的 Code! 
接下來將說明 `mutable` 與 const cast，他們將幫助我們破除 const 的限制，使程式設計更加靈活。

### Logical Constness
> 概念上的常數性 (Conceptual Constness)

我對這個論點的解讀是，某些 data 是藏於封裝底下，沒有暴露給 User 修改的。這種 member data 在 logical constness 的觀念下是可被修改的。
書中舉例，若我們在 `CTextBlock` 當中有一個快取 (cache) 的 member data ，用來記當前字串的長度。當字串沒有修改長度的行為(增加/減少)時，此快取都是有效的。但若有修改行為，則在 `length()` 被 Query 時，我們會需要更新這個快取。

在 Bitwise Constness 的觀念下，修改這個快取用途的 member data 是不合法的，且這也是 Compiler 的觀點。
解決辦法是，使用關鍵字 `mutable` 宣告這些有資格在 const function 內被改動的 data，`mutable` 使得 const function 在實踐上有討價還價的空間。

> `mutable` 釋放 non-static member data 的 bitwise constness 約束 (釋放 member data 的不可變動性)。


### Avoiding Duplication in const and Non-const Member Functions
> 當 const 和 non-const member function 有等價的實作時，讓 non-const 呼叫 const 可以避免 duplicated code。

若我們在 const & non-const function 當中，都有相同的程序要做: 邊界檢查、write log、verty data...，即使子步驟都可以抽出來，還是造成「走 flow 的流程」會重複在兩個 function 當中。

```cpp
class TextBlock 
{
	const char& operator[](std::size_t position) const;
	char& operator[](std::size_t position);
}
```

我們該做的是，把所有的東西寫在其中一個，而另一個去呼叫寫著 flow 的 function。這說明了我們的一個需求: 去除 Constness!

我懷疑這個手法在 C++11 & 14 可能有其他解，這裡先跳過細究。簡單來說就是透過 `const_cast` 將 const function 的結果再轉成非 const。

```cpp
class TextBlock {
public:  
	// same as before
    const char& operator[](std::size_t position) const {
        return text[position];
    }
	// now just calls const op[]
    char& operator[](std::size_t position) 
    {
        // cast away const on op[]’s return type
        // add const to *this's type, call const version of op[]
        return const_cast<char&>(\
	        static_cast<const TextBlock&>(*this)[position]
		);
    }
};
```
 