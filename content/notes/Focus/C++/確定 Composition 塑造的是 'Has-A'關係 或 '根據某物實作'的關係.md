---
title: "確定 Composition 塑造的是 'Has-A'關係 或 '根據某物實作'的關係"
date: 2023-05-07 15:52
tags:
- cpp
---

## Has A 關係
"Has-A" 指的是擁有一個 應用域 (application domain) 的物件，像是 
- Person 'has a' name.
- Person 'has a' address
- ...
這沒什麼爭議。

## 根據某物實作出的關係
這是指 實作域 (implementation domain)，表示 is-implemented-in-terms-of 關係。像是
- buffer
- mutex
- search tree

這麼說還是很抽象，舉例: 
std::set 是一個以平衡樹實作的資料結構，每一個元素需要耗費三個 pointer，它重視速度大於空間用量。若我們有一個「空間用量比速度更重要」的需求，則無法使用 std::set，有需求自己撰寫 Template。
現在，我們經歷了這一串掙扎: 

1. 實作 set 有很多種方法，想採用 linked list 的作法。
2. 想到了 std::list 就是這樣的資料結構，我該繼承它嗎?
3. 一旦繼承就代表 IS-A 關係，適用於 std::list 的每件事，這個新的 set 都可以接受
4. 但是 std::list 允許重複的元素出現在容器中，set 不允許，在插入新元素 (insert) 時會做處置。這違反了 IS-A 規則。
5. 不適合使用繼承。

### 以一個 Private member data 擁有 (has a) 一個 std::list container
正確的做法是，讓 Set 物件是根據一個 std::list 物件實作出來。我們會以一個 private member data 去 own (has a) 一個 std::list 物件，藉此達到 reuse linked list 的需求。

```c++
template<class T> // the right way to use list for Set
class Set {
public:
	bool member(const T& item) const;
	void insert(const T& item);
	void remove(const T& item);
	std::size_t size() const;
private:
	std::list<T> rep; // representation for Set data 
};

// 取一個函式實作舉例
template<typename T>
std::size_t Set<T>::size() const
{
return rep.size();
}
...
```

對於每個 member function 的實作，在 own 了一個 `std::list` container 之後，可以很輕易的呼叫 std::list API 達到我們的需求，達到 reuse 的目的。甚至相當適合把這些 function 寫成 inline function! 

不過在做 inline 之前，先檢視 [[了解 Inline 的裡裡外外]]。
