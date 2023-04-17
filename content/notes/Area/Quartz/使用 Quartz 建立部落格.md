---
title: "使用 Quartz 建立部落格"
categories:
- Quartz
---


## Install

1. Git
2. Go lang
3. Hugo: 需要手動加環境變數
4.  `go-obsidian`
    ```go
    go install github.com/jackyzha0/hugo-obsidian@latest
    ```
5. **Optional**  `make` `: Windows 下須使用 MinGW 安裝，參考: [C++ 開發環境 在 Windows 11 中安裝 mingw-w64 及設定環境變數](http://kaiching.org/pydoing/cpp-guide4/how-to-install-mingw-w64-and-set-environment-variable.html)

Hugo 需要以 PowerShell](https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows) 或 WSL , Git Bash 這種 linux-based terminal 運行。

## Start to Quzrtz
官方網站有相關的教學: 
- https://quartz.jzhao.xyz/notes/setup/
- https://quartz.jzhao.xyz/notes/obsidian/

以下我將擷取最短步驟
### 摘要步驟

1. Fork quartz 的 Github 專案，並 clone 到 Local。
2. 在 Clone 下來的倉庫中找到資料夾 `content`
3. 在 `content` 資料夾中創建 Obsidian 倉庫，或是把既有的倉庫內容放到 content 裡面。
4. 將 Obsidian 倉庫轉換成 Hugo 可用的

    ```bash
     hugo-obsidian -input=content -output=assets/indices -index -root=.
    ```

    需要注意，markdown 檔名不可以有 `.`，且每一篇文章都要有 metadata: 在頁首有 `title` 的資訊，如下: 

    ```markdown
    ---
    title: "Private Stuff"
    ---
    ```

    其實有更多的 meta-data 可以設定，可以看 quartz 給的範例。由於使用 quartz 創建模板必須要 metadata，[作者建議](https://quartz.jzhao.xyz/notes/obsidian/)可以直接在 Obsidian 裡面創建模板，讓每新增一個模板都有這些資訊! 

5. 啟用 Hugo Server

    ```bash
     hugo server --enableGitInfo --minify 	# render faster
     hugo server --disableFastRender 		# search bar will enable
    ```


## 關於 Obsidian 模板功能
- 可以參考此文介紹如何建立模板 [【Obsidian 使用教學】筆記篇 05 — 結合資訊處理流程，讓筆記的 Metadata 變得更詳細](https://medium.com/pm%E7%9A%84%E7%94%9F%E7%94%A2%E5%8A%9B%E5%B7%A5%E5%85%B7%E7%AE%B1/obsidian-%E4%BD%BF%E7%94%A8%E6%95%99%E5%AD%B8-%E7%AD%86%E8%A8%98%E7%AF%87-05-%E7%B5%90%E5%90%88%E8%B3%87%E8%A8%8A%E8%99%95%E7%90%86%E6%B5%81%E7%A8%8B-e6a953438f43)
- 要注意，插入模板的時候，需要打完檔案名稱，並把 Insert 的鼠標要在 Header 1 下的第一行。

## 發佈到 Github Page

參考 

![[Publish Quartz to Github Page]]


## 修改首頁

如果想在首頁放置一些連結，引導到特定頁面，需要注意以下幾點: 雙向連結內放的是「相對於該頁面的路徑」，路徑對應的是檔案名稱。

1.  當檔案名稱有空白時，網址會以 `-` 取代空白，但在雙向連結的撰寫中不可以寫 `-`。
```
[[notes/Area/PKM/Setup Quartz]] # OK  
[[notes/Area/PKM/Setup-Quartz]] # Broken internal link
```
2.  注意結尾不要多加反斜線    
3.  主頁相對於各檔案都是以 `note/` 開始
