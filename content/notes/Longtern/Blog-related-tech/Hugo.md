---
title: Hugo
date: 2024-05-02 00:34
tags:
  - empty
---
## Hugo and go version 
Hugo 的版本必須與 go 相互搭配，否則會出現 `Error: failed to download modules: binary with name “go” not found` 之類的 error。

```bash 
hugo version 
go version
```
舉例來說，hugo v0.119.0 就需要跟 Go 1.21.1 搭配。

## Hugo Mod 

```
hugo mod clean 
hugo mod graph
```


## 將主題作為一個 Hugo Module 

### Initialize a Module 
嘗試從空白開始
```bash
mkdir customize-docsy
cd customize-docsy
hugo mod customize-docsy
# go.mod generated 
```
這時資料夾中會有一個 `go.mod` 的檔案，內容如下: 
```go
module customize-docsy

go 1.21.9
```

### Import from existing module 
創建一個檔案 `hugo.yaml`，內容如下: 
```go
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
如果想把 module 導向 local 的位置，可以使用 replacements。
有兩種方式，一種是寫在 go.mod，一種是寫在 hugo.yaml 
#### go.mod
[source](https://gohugo.io/hugo-modules/use-modules/#make-and-test-changes-in-a-module)

```
replace github.com/bep/hugotestmods/mypartials => /Users/bep/hugotestmods/mypartials
```

#### Hugo.yaml 
[source](https://gohugo.io/hugo-modules/configuration/#module-configuration-top-level)
如同範例中的註解寫到，如果想把 "github.com/google/docsy" 導向 local 的 docsy，就把該行 unconmment: 

```yaml
replacements: "github.com/google/docsy -> ../../docsy"
```

### Download Necessary Modeul 
```go
hugo mod graph
hugo server 
```
Go to "localhost:1313"，因為是從頭創建，目前是一片空白。

### 學習使用 Config
官方建議從 example copy 來，或這裡有[一些範例網站](https://www.docsy.dev/docs/examples/)可以參考
[Basic Config](https://www.docsy.dev/docs/get-started/basic-configuration/)
[kubeflow 的 config 宜參考](https://github.com/kubeflow/website/blob/master/config.toml)

Minize Config (參考自 kubeflow)

```yaml
baseURL : "/"
title : "Customize"
description : "Kubeflow makes deployment of ML Workflows on Kubernetes straightforward and automated"

###############################################################################
# Docsy
###############################################################################
enableGitInfo : true
# language settings
contentDir : "content/en"
defaultContentLanguage : "en"
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

### 為類別建立類別首頁
現在，local 網站上有 "Event, Docs, Blogs" 幾個 tab，但點進去內容卻是空的。

```bash 
mkdir -p content/zh-tw
cd content/zh-tw
mkdir blog 
cd blog
touch _index.md
```
並編輯 `_index.md` 的內容: 

```markdown
---
title: Blog
menu: {main: {weight: 30}}
---
Content here won't show in HTML.
```

Docsy 會偵測資料夾的名稱，決定套用的 layout。也可以在 markdown meta data 當中指定 type 套用模板。
```
type: blog
```

參考的 [layouts](https://github.com/google/docsy/tree/main/layouts) 。
不同的 layout 有不同的特點，在範例網頁中，`blog` 下又有兩個資料夾 : "News", "Releases"，文章會列在左邊欄位 (電腦版面)，並且會有 RSS 訂閱按鈕。
注意`blog` layout 的 `_index.md` 內文的部分是不會顯示出來的! 


Docs layout 沒有 RSS 訂閱按鈕，且 `_index.md` 的內容會顯示在 HTML 上。





## If you have above knowledge
https://www.docsy.dev/docs/get-started/docsy-as-module/start-from-scratch/

```bash
hugo new site my-new-site
cd  my-new-site
hugo mod init github.com/me/my-new-site
hugo mod get github.com/google/docsy@v0.10.0
cat >> hugo.toml <<EOL
[module]
proxy = "direct"
[[module.imports]]
path = "github.com/google/docsy"
EOL
hugo server

```