---
title: "以 Hugo 發佈簡單的頁面"
date: 2023-04-09
categories:
- hugo
description: 以 hugo 建立部落格的範例，無關 quartz
---
## Hugo 建立部落格的範例

直接用 Hugo 建立部落格，不使用 Quartz 的範例:

### Start
```bash 
hugo new site quickstart  
cd quickstart  
git init  
git submodule add https://github.com/theNewDynamic/gohugo-theme-ananke themes/ananke  
echo "theme = 'ananke'" >> config.toml  
hugo server
```

## Add a content page 
```
hugo new content my-first-post.md
```



[https://gohugo.io/getting-started/quick-start/](https://gohugo.io/getting-started/quick-start/)

### 將 Markdown 檔案轉換成 Web Page
下兩者擇一即可

```bash 
hugo server --buildDrafts  
hugo server -D
```

index.html 通常沒有內容，想要知道剛才新增的夜面有沒有成功登記在案，可以去: http://localhost:1313/sitemap.xml


主題會有自己的 `config.toml`，通常會在該主題 github 的 example site (可能是一個資料夾或專案) 底下，以 hugo-coder 為例，在把主題載到 `themes/hugo-coder` 底下之後: 

```bash
cp themes/hugo-coder/exampleSite/config.toml .
```

這樣就不用重零配置。但需要注意，啟用 `hugo server ` 時，預設讀取的設定檔是 `hugo.toml`，而主題提供的預設設定檔案通常是 `config.toml`。想要直接使用 `config.toml` 需要指定參數: 

```bash
hugo server -D --config config.toml
```

## docsy
Docsy 需要用到 `npm` 以及 `hugo-extension`

```bash
hugo new site test-docsy  
cd test-docsy
git init  
git clone --depth 1 https://github.com/me/example.git themes/docsy
## 安裝 docsy 獨有的依賴項目
cd themes/docsy/userguide/
npm install
npm run serve
cd ../../../ # root of test-docsy
###
echo "theme = 'docsy'" >> config.toml  
hugo server
```



### Bug: binary go not found...
注意 hugo build 的版本與當前 go 的版本是否一致!


## Coder 
```bash 
hugo new site quickstart  
cd quickstart  
git init  
git submodule add https://github.com/luizdepra/hugo-coder themes/hugo-coder  
echo "theme = 'ananke'" >> config.toml  
hugo server
```

## Resource 
[Hugo 從零開始 建立自己的部落格](https://devbricker.github.io/post/hugo/deploy/hugo_build1/)
[用 Hugo 來寫文章吧](https://tonypepe.com/posts/hugo/hugo)