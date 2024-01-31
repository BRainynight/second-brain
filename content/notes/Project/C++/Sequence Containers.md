---
title: Sequence Containers
date: 2024-01-28 19:07
tags:
  - cpp
---

## Complexity 
`O(1)`: 與容器的 size 無關，具有 constant runtime，但兩個容器的 complexity 都是 `O(1)` 並不表示相同的操作有相同的速度，僅表示不隨著容器的增加而影響 runtime。

- `std::array` : homogeneous container of fixed length.
- `std::vector` : homogeneous container, which length is automatically adjusted at runtime.

| Container | homogeneous | length | Memory is continusous |
| ---- | ---- | ---- | ---- |
| `std::array` | Yes | fixed |  |
| `std::vector` | Yes | Adjust at runtime. | Yes |
| `std::deque`  | Yes | fixed | 多段 std::array 所組成的 sequence |
|  |  |  |  |
## std::array 

結合了 C array 的特性以及 `std::vector` 的 interface。
Index access 有三種方式
1. `arr[n]`: 不會 check index out of range
2. `arr.get(n)`: 當 index out of range 時會拋出 `std::range-error` exception.
3. `std::get<n>(arr)`

## std::vector
注意 initialize std::vector 時，`{}` 是 [[Initializer List]]，與 `()` 的意思是不同的。
```cpp
std:: vector < int >( 10, 2011) // 10 個元素都是 2011 
std:: vector < int >{10, 2011}  // 2 個元素，分別是 10 跟 2011
```

### size 與 capacity 
- `size` : 表示容器當前的元素數量
- `capacity`:  是在不 reallocate 記憶體的情況下，能夠有多少個元素。
- `resize(n)`: 將容器的 size 增加到 n
- `reserve(n)`: 保留最後 n 個 elements 的 memory 
- `shrink_to_fit()`: 減少沒用到的 capacity ，這只是一個請求 ([no-binding request](https://en.cppreference.com/w/cpp/container/vector/shrink_to_fit#:~:text=vector%3A%3Ashrink_to_fit&text=It%20is%20a%20non%2Dbinding,to%20the%20elements%20are%20invalidated.))，implementation 可以自行決定是否真的執行。


## std::deque
由很多段 `std::array` 組成的 sequence 

## std::list 
雙向 linked list，雖然介面都很像，但實作非常不同
1. 不支援 random access 
2. access 任意 element 非常慢，因為要 iterate 
3. 加/減 elements 很簡單，接一下 pointer 而已
4. 加/減 elements 後，iterator 依然有效。
## std::forward_list
- 單向 linked list，比 memory 需求比較少。
- iterator 不支援 `it--`
- 是唯一不知道自己 size 的 container
- 