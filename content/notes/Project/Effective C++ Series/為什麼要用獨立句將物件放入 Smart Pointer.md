
> 盡可能確保 `new` 出來的物件，可以立即被放入 smart pointer 裡面，避免任何額外的步驟。只要有多餘的步驟，就可能因為意外而使得 smart pointer 沒有真正掌控到資源。

以獨立一句話將 newed 物件加入 smart pointer，格式如下

```cpp
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
```

---

其原因是，如果像以下寫法
```cpp
processWidget(std::shared_ptr<Widget> pw(new Widget), priority());
```

編譯器要做的有三件事
1. 呼叫 `priority`
2. 執行 `new` 
3. 呼叫 smart pointer constructor

而我們無法確保這三件事的最終順序為何，必然的關係只有 「會先 `new` ，再執行 smart pointer constructor」。而 `priority` 是**可能**安插於 new 之後的。

1. `new` 
2. `priority` (發生錯誤)
3. smart pointer constructor

如果不幸的，編譯器選擇這種順序，並且在把物件放入 smart pointer 之前發生了錯誤，這塊記憶體將沒有 smart pointer 協助銷毀! 
>