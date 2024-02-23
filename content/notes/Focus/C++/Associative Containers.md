---
title: Associative Containers
date: 2024-01-14 20:54
tags:
  - cpp
  - stl
---
Chapter5
## Associative Containers
- Unordered containers have better performance.

| | Unordered Container | Ordered Container |
| --- | --- | --- |
| Access Time | Constant | Logarithmic |
	
## Ordered Container 

### map & multimap 

對 key 與 value 有一些規定
1. Key: sortable 
2. Value: default Constructible 
3. 兩者皆須  copyable, movable 

> 懷疑這邊 default constructible 是否為硬性規定，還是在試圖呼叫 operator[] 的時候 compile 不會過? 

比較準則 (comparison criterion) 預設是 `std::less`，如果是 User-defined type 則預設使用 operator `<` 排序。也就是說，如果 key 是 User-defined type 則必須 overload `operator<`。

比較準則可以替換，但必須遵守 strict weak ordering。比起重新定義一個 criterion，直接使用 STL 寫好的 comparison criterion 更快，像是 `std::greater` (template)。

### std::map 有如 associative array 
std::map 與 std::vector 一樣支援 `operator[]`，std::map 像是一個接受 index 為任意 type 的 vector。
此外，std::map 還支援 member function `at`，與 `operator[]` 的差別大概在於
- `operator[key]`: 當找不到 key 的時候，會自動 insert key & 創建 value
- `at(key)`: 當找不到 key 的時候，會引發 exception。
## Unordered Container
比起 Ordered Container，Unordered Container 擁有比較豐富的 API、並且 key 是未經排序的。
### Performance 
由於使用 hash function，unordered container 在 access 上的複雜度是 conostant，ordered 則是 `O(logn)`。
### Hash Function 
Unordered_map 把 indexes 儲存於 bucket 當中，

Hash function 決定兩件事
1. Index 應該存在哪一個 bucket
2. 把 key map 給對應的 index (hash code, hash value)

![[Simple Unordered association container.png]]
如果不同 key 對應到同一個 index，就稱為 collision，這應該避免。

Indexes 在 Bucket 當中通常以 linked list 的形式儲存，從 Key 取得 Value 時，access 到 bucket 的複雜度是 constant，但如果一個 bucket 中有兩個以上的 index，要拿到對應的 index 的複雜度是線性的。

- Capacity: bucket 的數量
- Load factor: 每個 bucket 中的元素平均數量

一個好的 hash function 應該盡量避免 collision，並且在放 index 於 bucket 時要均勻分布。

![[Hash Function-load factor.png]]
#### Rehash 
通常 C++ Runtime 中發現 load factor 超過 1 的時候就會新增 bucket (使得 access 的複雜度永遠是 constant)，這個過程就是 rehashing.

### API 
- `max_load_factor()`: 可以得到當前 container 所允許的 load_factor 最大值，透過設定這個數值得以影響 rehashing 跟 collision 的機率。
- `load_factor()`: 得到 bucket 當中元素數量的平均值。
- 
Example:https://en.cppreference.com/w/cpp/container/unordered_map


