---
title: "Hugo Publish Simple Page"
date: 2023-04-09
categories:
- hugo
description: 以 hugo 建立部落格的範例，無關 quartz
---
## Hugo 建立部落格的範例

直接用 Hugo 建立部落格，不使用 Quartz 的範例:

### Start

hugo new site quickstart  
cd quickstart  
git init  
git submodule add https://github.com/theNewDynamic/gohugo-theme-ananke themes/ananke  
echo "theme = 'ananke'" >> config.toml  
hugo server

[https://gohugo.io/getting-started/quick-start/](https://gohugo.io/getting-started/quick-start/)

### 將 Markdown 檔案轉換成 Web Page

hugo server --buildDrafts  
hugo server -D
