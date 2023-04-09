---
title: "可使用的metadata"
date: 2023-04-09
categories:
- blog
slug: usable meta data
---

Source: https://gohugo.io/content-management/front-matter/

舉例:

```yaml
categories:
- Development
- VIM
date: "2012-04-06"
description: spf13-vim is a cross platform distribution of vim plugins and resources
  for Vim.
slug: spf13-vim-3-0-release-and-new-website
tags:
- .vimrc
- plugins
- spf13-vim
- vim
title: spf13-vim 3.0 release and new website
```

可建立 Obsidian 模板:

```
title: 
date: {{date}}
description: 

slug: alias-name
tags:
- default
categories:
- default

```

本頁所使用的 metadata: 
```
title: "可使用的metadata"
date: 2023-04-09
slug: usable meta data # 網址變成此名稱
categories:
- blog
```

這裡，我讓檔案名稱變成
- filename: `Hugo front matter.md` 
- title: `可使用的metadata` > 頁面標題
- slug: `usable meta data` > 連結名稱


## Category vs. Tag

在打造第二大腦中，作者提出 Tag 是一種打破資料夾邊界的連結方式。我希望，在我的部落格中，我希望讓網頁會 Category 做資料夾壁壘的分類，有必要時再以 tag 打破邊界。

但似乎 quartz 支援的只有 tags 而沒有 categories。我想參考這篇文章試試看能不能打開該功能: 
https://ithelp.ithome.com.tw/articles/10244921