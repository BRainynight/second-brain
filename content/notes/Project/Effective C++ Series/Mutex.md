---
title: "Item14"
date: 2023-05-01 23:15
tags:
- cpp
---
假設我們用 C API 處理 `Mutex` 物件
```cpp
void lock(Mutex *pm); // lock mutex pointed to by pm
void unlock(Mutex *pm); // unlock the mutex
```

使用者需要自己手動分別呼叫 `lock` 與 `unlock`。為了確保不會忘記幫 Mutex 解鎖，可以建立一個由 RAII 守則支配的 Class --資源在建構期間獲得(lock)，在解構期間釋放(unlock)--來管理資源「Mutex 物件」。

```cpp
class Lock {
public:
explicit Lock(Mutex *pm) : mutexPtr(pm) 
	{ lock(mutexPtr); } // acquire resource
~Lock() { unlock(mutexPtr); } // release resource

private:
Mutex *mutexPtr;
};

```
而客戶端調用，也符合 RAII 方式
```cpp
Mutex m;     // define the mutex you need to use
...
{            // create block to define critical section
Lock ml(&m); // lock the mutex
...          // perform critical section operations
}            // automatically unlock mutex at end of block
```
現在，客戶在也不會因忘記為  `unlock(Mutex)` 而出問題!

## 如果有人試圖複製 `Lock` ?