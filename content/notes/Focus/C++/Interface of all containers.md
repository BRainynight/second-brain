---
title: Interface of all containers
date: 2024-01-24 23:46
tags:
  - cpp
---

每個 Container 至少會有一個 type parameter 與該 type 的 allocator，allocator 多數時候在背景運行 (在需要它的時候默默調用，user 不需要直接呼叫 allocator)。
以 `std::vector` 為例，`std::vector<int>` 實際上呼叫的是 `std::vector<int, std::allocator<int> >`。有了 `std::allocator`，你可以動態的調整除了 `std::array` 之外，所有 container 的 size。
## Create and Delete
STL containers 基本上擁有相似的介面

## Size
判斷容器是否為空，建議使用 `empty` 
1. `empty()` 的速度比 `size()==0` 快。
2.  `std::forward_list` 沒有 member function `size`，使用 `empty` 更 general 一點。

另外 `max_size()` 可以取得 container 所能擁有的最大成員數量，這是個數值是 [[Implementation-defined]] ，取決於編譯器。

## Access (Iterator)

For a container cont, you get with cont.begin() the begin iterator and with cont.end() the end iterator, which defines a half-open range. It is half-open because the begin iterator belongs to the range, and the end iterator refers to a position past the range. The iterator pair cont.begin() and cont.end() enables it to modify the elements of the container. Creation and deletion of a container Iterator

Rainer Grimm. The C++ Standard Library (Kindle Locations 2391-2395). Kindle Edition. 


## Assign and Swap 
- Assignment: 分成 
	1. copy assignment
	2. moving assignment
	3. 透過 initializer list assign，此方法不適用 `std::array`
- swap 有兩種形式
	1. 透過 member function `swap`
	2. 透過 function template `std::swap`

```cpp
# assignment 
cont1 = cont2; // copy assignment 
cont1 = std::move(cont2); // moving assignment

// assign with initializer list, excluding for std::array
cont = {1, 2, 3};

# swap 
cont.swap(cont2);
std::swap(cont, cont2); 

```

## Compare 

兩個容器之間的比較運算符，會逐一比較兩個容器中的元素。比較 associative containers 時，是以 key compare。Unordered associative containers 只支援 `==` 跟 `!=`。
## Erasure 
自 [C++20 起](https://en.cppreference.com/w/cpp/container/vector/erase2)，STL 提供了兩個 free functions (並非容器的 member functions) 。
`std::erase(container, val)`, `std::erase_if(container, pred)` 會清除容器裡面滿足條件的所有元素，兩個 function 的回傳值都是那些被清除的 elements。


