---
title: 從零開始 docsy
date: 2024-05-03 13:47
tags:
  - empty
---
本文的使用 docsy@0.10.0，hugo version 和 go version 分別為
```
go version go1.20.2 windows/amd64
hugo v0.119.0+extended windows/amd64 BuildDate=unknown
```
注意 hugo 對 go 的版本有要求，錯誤的版本將無法執行 hugo command。

## 開始之前

使用主題有[多種方式](https://www.docsy.dev/docs/get-started/#installation-options)，官方最建議使用 Hugo Module 加載主題

本文將參考 [docsy-example](https://github.com/google/docsy-example)，嘗試用最少的設定從頭創建一個 docsy theme 的網站。

## 初始化 Hugo Module 
嘗試從空白開始
```bash
mkdir customize-docsy
cd customize-docsy
hugo mod customize-docsy
# go.mod is generated 
```

這時資料夾中會有一個 `go.mod` 的檔案，內容如下: 
```go
module customize-docsy

go 1.21.9
```

接下來
```bash 
hugo mod get github.com/google/docsy@v0.10.0
```

`go.mod` 的內容會多一行 require docsy 
```go
module customize-docsy

go 1.21.9

require github.com/google/docsy v0.10.0 // indirect

```

## 設置 hugo.yaml
import 的部分參考 docsy-example 創建一個檔案 `hugo.yaml`，內容如下: 
```yaml
module:
  # uncomment line below for temporary local development of module
  # replacements: "github.com/google/docsy -> ../../docsy"
  proxy: "direct"
  hugoVersion:
    extended: true
    min: "v0.119.0+extended"
  imports:
    - path: "github.com/google/docsy"
      disable: false
    - path: "github.com/google/docsy/dependencies"
      disable: false

```

### Replacement 
如果想把 module 導向 local 的位置，可以使用 replacements。有兩種方式，一種是寫在 go.mod，一種是寫在 hugo.yaml 
#### go.mod
[Reference](https://gohugo.io/hugo-modules/use-modules/#make-and-test-changes-in-a-module)

```go
replace github.com/bep/hugotestmods/mypartials => /Users/bep/hugotestmods/mypartials
```

#### Hugo.yaml 
[Reference](https://gohugo.io/hugo-modules/configuration/#module-configuration-top-level)
如同範例中的註解寫到，如果想把 "github.com/google/docsy" 導向 local 的 docsy，就把該行 unconmment: 

```yaml
replacements: "github.com/google/docsy -> ../../docsy"
```

## 下載相關模組並執行
```bash
hugo mod graph
hugo server 
```
前往 "localhost:1313"，因為是從頭創建，目前是一片空白。至此，已經成功套用主題，並且啟動 server。


---
# Section2 : Config
## 學習使用 Config
Config 內容繁雜，參考既有的會比較容易。個人認為 docsy-example 的 config 不容易參考，下面將提及另一個資源更容易讀。官方列出了[一些範例網站](https://www.docsy.dev/docs/examples/)，可以前往他們的 Github 找 config 參考。這裡提供兩個連結: 
- [Docsy official: Basic Config](https://www.docsy.dev/docs/get-started/basic-configuration/): 官方的文章
- [kubeflow Config](https://github.com/kubeflow/website/blob/master/config.toml): 較簡單，且 config 有分區寫 comment，比官方範例網站更容易讀。

## 簡易 Config
參考自 kubeflow，我設置了最簡易的 config，讓啟動的網站有 Top-level navigation，不再是一片空白。

```yaml
baseURL : "/"
title : "My Site"
description : "This is a site with min settings."

###############################################################################
# Docsy
###############################################################################
enableGitInfo : false
# language settings
contentDir : "content/zh-tw"
defaultContentLanguage : "zh-tw"
# tell Hugo not to include the /en/ element in the URL path for English docs
defaultContentLanguageInSubdir : false
# useful when translating
enableMissingTranslationPlaceholders : true
# disable taxonomies
disableKinds : ["taxonomy"]
# deprecated directories
ignoreFiles : []

###############################################################################
# Hugo - Top-level navigation (horizontal)
###############################################################################

menu:
  main:
    - name: "Events"
      weight: -102
      pre: "<i class='fas fa-calendar pr-2'></i>"
      url: "/events/"
    - name: "Docs"
      weight: -101
      pre: "<i class='fas fa-book pr-2'></i>"
      url: "/docs/"
    - name: "Blogs"
      weight: -100
      pre: "<i class='fas fa-rss pr-2'></i>"
      url: "/blogs/"
    - name: "GitHub"
      weight: -99
      pre: "<i class='fab fa-github pr-2'></i>"
      url: "https://github.com/kubeflow/"
```

## 為類別建立類別首頁
現在，local 網站上有 "Event, Docs, Blogs" 幾個 navigation option，但點進去內容卻是 Not found 。接下來將為各 option 建立該類別的首頁。

```bash 
mkdir -p content/zh-tw
cd content/zh-tw
```

因為保留了 multiple language，並且設置主語言為 "zh-tw"，所有的內容要放在 "content/zh-tw" 底下。

```bash
mkdir blog 
cd blog
touch _index.md
```


並編輯 `_index.md` 的內容: 

```markdown
---
title: Blog
---
Content here won't show in HTML.
```

再起一次 `hugo server`，blog 的頁面不再是 404，而是一片空白。反觀 docs 頁面還是404，說明這個 index page 是有效的。

## Layouts
Docsy 會偵測資料夾的名稱，決定套用的 layout。至於支援哪些類別，參考的 [layouts](https://github.com/google/docsy/tree/main/layouts) 。沒有特別列出來的類應該是套用 `_default`。

### blogs
不同的 layout 有不同的特點，在 docsy-example 中，`blog` 下又有兩個資料夾 : "News", "Releases"，文章會列在左邊欄位 (電腦版面)，並且會有 RSS 訂閱按鈕。
注意`blog` layout 的 `_index.md` 內文的部分是不會顯示出來的! 
### docs
Docs layout 沒有 RSS 訂閱按鈕，且 `_index.md` 的內容會顯示在 HTML 上。

### 手動設定套用的 layout
我們也可以在單一 markdown file 中，設置 meta data 指定 type 套用模板。
```
type: blog
```

### 設定整個資料夾套用的類別
每篇文章逐一設置不夠方便，如果我有一個類別為 "Notes" (content/zh-tw/notes)，但想套用 "docs" layout: 
1. 在 notes 資料夾底下創建 `_index.md`
2. 設置 `_index.md` 內容如下

```markdown
---
title: Notes
description: "Add description here"
cascade:
- type: "docs"
---
Some content
```

### Search Engine
總共有[三種](https://www.docsy.dev/docs/adding-content/search/)，我選最簡單的 [Local search with Lunr](https://www.docsy.dev/docs/adding-content/search/#local-search-with-lunr)。用 Java Script 做 local 的站內搜索: 
```yaml
params:
  offlineSearch: true
```

### Dark/Light Mode 

```yaml
params:
  ui:
    showLightDarkModeMenu: true
```

## Section3: 正式上線
[Docsy 官方](https://www.docsy.dev/docs/get-started/docsy-as-module/start-from-scratch/)有提供「白手起家」的 command 該怎麼寫: 

```bash
# initialize site 
hugo new site my-new-site
cd  my-new-site
# init mod and add require 
hugo mod init github.com/me/my-new-site
hugo mod get github.com/google/docsy@v0.10.0
# add config
cat >> hugo.toml <<EOL
[module]
proxy = "direct"
[[module.imports]]
path = "github.com/google/docsy"
EOL
hugo server

```

透過 `hugo new site`，`hugo` 會創建一些預設的資料夾，如 `content`, `assets` 等，不像前面得自己創建。
在先前的簡易範例中只改 config，無須更改網頁主體的內容，因此有無這些其他資料夾無直接影響。在實際上線時，要覆蓋 docsy 預設的 CSS 都得在 `assets/scss` 下加檔案，因此還是用 `hugo new site` 生成完整的架構。

## 使用 Github Page 架站
上網搜尋「架站」，已經可以找到許多資源，這裡不多贅述。如果從未有架站經驗，強烈建議閱讀這篇文章: [技術網站架設經驗雜談](https://www.ithome.com.tw/voice/148476)。先決定: 是否要付費買網域? 

對我來說，部落格像是一個 Side Project。不曉得更新頻率，也不曉得持續到甚麼時候，用且對 Github Page 已有經驗，因此決定繼續使用。Github Page 有一些[限制](https://docs.github.com/zh/pages/getting-started-with-github-pages/about-github-pages#usage-limits)，如果都可接受，那就繼續吧! 
### 關於 Github Page
每個人的帳戶對應的網域名稱是: `<username>.github.io`，以我來說就是`brainynight.github.io`。

你可以擁有多個 github page，但 `<username>.github.io` 只能對應一個專案，這個專案的名稱就必須跟網域有一樣的名稱。像這個網站對應的專案就是: [brainynight.github.io](https://github.com/BRainynight/brainynight.github.io) 。如果有多個 Github Page 需求，其他 Page 會變成 `<username>.github.io/<repository-name>`，被設成 Github Page 的專案必須是 Public 的。

### 步驟
具體步驟參考[官方說明](https://docs.github.com/zh/pages/quickstart)，使用 Hugo 還牽涉到 github action，這裡簡單修改步驟。
1. 創建一個新的 repository，輸入 `<username>.github.io` 作為名稱
	1. 如果是第二個 Github Page (已經有另一個 repository 名為`<username>.github.io`)，這裡就輸想要的名稱就好 (ex. second-blog)。
2. 把剛才 `new site` 生成出的內容上傳到 Github repository
3. 進到 repository，點設定
4. 找到 "Pages" 的設定頁面
5. **不同於 Github 教學文章!** 在 "Build and deployment" 選擇 "Github Actions"，參考 [Hugo-Host on GitHub Pages](https://gohugo.io/hosting-and-deployment/hosting-on-github/)的 Step4
6. 在 Local repository，創建檔案 `.github/workflows/hugo.yaml`，內容複製 Hugo 說明的 Step6。記得 **Branch Name 跟 Hugo Version 要手動改成自己使用的版本!**。這個 Github Action 的觸發條件是當有內容 "push" 的時候。
7. 在 Local repository commit 並且上傳到 Github
8. 回到 Github repository，點選分頁 "Actions"，會看到有 workflow 清單，由於剛才設的動作是「當 Push 的時候執行」，因此現在正在跑。如果失敗了可以一步步點進去看 error message。
	![All workflows](https://gohugo.io/hosting-and-deployment/hosting-on-github/gh-pages-3.png)
9. 成功的話如下圖，可以到自己的網站看 Hugo Build 出來的內容了!
	![success](https://gohugo.io/hosting-and-deployment/hosting-on-github/gh-pages-4.png)


## 失敗經驗

在實際部屬時遇到問題: 
```
Error: error building site: POSTCSS: failed to transform "scss/main.css" (text/css). Check your PostCSS installation; install with "npm install postcss-cli". See [https://gohugo.io/hugo-pipes/postcss/:](https://gohugo.io/hugo-pipes/postcss/:) binary with name "npx" not found
```

我的解法參考自 [Hugo: postcss](https://gohugo.io/hugo-pipes/postcss/)，在自己 Local 的專案資料夾執行指令: 
```bash 
npm i -D postcss postcss-cli autoprefixer
```

下指令後會下載一堆模組，把他們都加到 git 裡面，一起推上 github，我不確定是否為最佳解，不過問題解決了。