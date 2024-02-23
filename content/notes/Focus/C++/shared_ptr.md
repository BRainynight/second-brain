---
title: shared_ptr
date: 2023-12-25 19:48
tags:
  - cpp
---
[shared_ptr in cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr)

> Constructing a new `shared_ptr` using the raw underlying pointer owned by another `shared_ptr` leads to undefined behavior.

shared pointer 是資源管理物件，它內部會儲存一個 couting，計算有幾個 shared_ptr 使用中。當一個 shared_ptr 消失，則 couting 減一，直到 couting 歸零則 release 這個物件的 memory。
然而，維持這個記數的正常運作有一個前提: 所有的 shared_ptr 都是從第一個 shared_ptr COPY 而來。使用 raw pointer 去製造一個新的 pointer 無法保證這個機制正確。

## 實際案例
此例中，
1. new 了一個 A 物件的 raw pointer 
2. 放進 sm_ptr1
3. 取 A 物件的 reference 
4. 對此 reference 物件取 address
如果使用 `std::cout` 印出 `sm_ptr1`, `raw_ptr`, 對 reference 取的 address 都會得到同一個結果。
然而，如果把 (4) 取出的 address 拿去再建一個 shared_ptr (5) 出來，情況就不同了。

現在有兩個 shared_ptr，但把 `use_count()` 印出來卻都是 1。在執行期間發生了更糟糕的事: `free(): double free detected in tcache 2`。

這應該是因為同一個 memory 被 free 了兩次的意思。原因是，有兩個 shared pointer 沒有共享計數，在 main loop 走到最尾端的時候，一個 shared_ptr 被消滅、同時把 A 物件的 memory 也清掉了，第二個 shared_ptr 被消滅時，也試圖做相同的事情，故而引發此問題。


```cpp
class A { ... }
int main()
{
    A* raw_ptr = new A(); // (1)
    auto sm_ptr1 = std::shared_ptr<A>(raw_ptr); // (2)
    std::cout<<"Raw ptr  "<< raw_ptr << std::endl;
    std::cout<<"Smartptr1 "<< sm_ptr1 << " " << sm_ptr1.use_count() << std::endl;
    A& ref = *sm_ptr1; // (3)
    std::cout<<"&(*sm_ptr1)  "<< &ref << std::endl; // (4)
    
    auto sm_ptr2 = std::shared_ptr<A>(&ref); // (5)
    std::cout<<"Smartptr2 "<< sm_ptr2 << " " << sm_ptr2.use_count() << std::endl;
    std::cout<<"Smartptr1 "<< sm_ptr1 << " " << sm_ptr1.use_count() << std::endl;

    std::cout<<"end"<<std::endl;
}
```
Output
```
Raw ptr  0x55be93224eb0
Smartptr1 0x55be93224eb0 1
&(*sm_ptr1)  0x55be93224eb0
Smartptr2 0x55be93224eb0 1
Smartptr1 0x55be93224eb0 1
end
free(): double free detected in tcache 2
Aborted
```


## enable_shared_from_this
C++11 在導入 smart pointer 的同時，也還提供了 [enable_shared_from_this](https://en.cppreference.com/w/cpp/memory/enable_shared_from_this) 這個工具。
然而，這個工具不能解決上面被 free 兩次的問題。

想要透過 `enable_shared_from_this` 取得技術正確的 shared_ptr，你必須
1. 拿到第一個 shared_ptr 
2. 透過對第一個 shared_ptr 呼叫 [smartPtr->shared_from_this](https://en.cppreference.com/w/cpp/memory/enable_shared_from_this/shared_from_this "cpp/memory/enable shared from this/shared from this")的方式取得第二個 shared_ptr
如果都能夠拿到第一個 shared_ptr 的話，又何必多此一舉? 直接 Copy 就好了!

[這篇文章](https://kheresy.wordpress.com/2018/08/08/enable_shared_from_this/)提供了一個觀點: 
1. `enable_shared_from_this` 是為了讓 class 內部可以取得自身物件的 shared_ptr。
2. 給 call back 架構使用

第一點的部分，在沒有這個工具時，假如試圖在 class 裡面寫這種函式提供 shared_ptr，事實上每一個呼叫函式的人拿到的都是不同的資源管理器，指向同一個物件，就會產生 free 多次的問題。至於第二點，參見[文章範例](https://kheresy.wordpress.com/2018/08/08/enable_shared_from_this/)。

```cpp
// wrong method
A::get_shared_ptr()
{
	return std::shared_ptr<A>(this);
}
```


