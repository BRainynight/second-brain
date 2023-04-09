---
title: "將Quartz發佈到Github Page"
categories:
- Quartz
tags:
- Quartz
---
由於我對 github action 不熟悉，在設置到 github page 的時候遇到了一點困難...。

首先，如果專案是從 templage fork 過來的，它應該分成 `hugo` 跟 `master` 兩個 branch。其中

- `hugo`: 存放 config, markdown files (`content` 底下) 的地方
- `master`: 利用 github action 把專案內容轉成靜態網頁

我因為是 clone 下來再 push 到自己的專案，沒有遵守這兩個命名方式而遇到了一點困難。在我的專案中，`main` 對應的是存放 markdown files (轉換前) 的 page，`publish` 才是 github page 再生成時所根據的 branch。

## 設置 Github Action 

如作者的[教學](https://quartz.jzhao.xyz/notes/hosting/)所說，首先要打開 workflow permission。位置是 `Setting > Action > General`。

![Set workflow Permission](https://quartz.jzhao.xyz/notes/images/github-actions.png)

## 設置 Github Page 

在 `Setting > Pages` 當中，將設置 Source 項目的 branch 設成 `master` (我則是設成 `pubslish`)。Domain name 除非自己有特別買網域，否則不用動。

![Github page setting](https://quartz.jzhao.xyz//notes/images/github-pages.png)

## Domain Name 

一共會影響兩個地方:

- `config.toml`
- `.github/workflows/deploy.yaml`

如果用 github 預設的網址會是 `<YOUR-GITHUB-USERNAME>.github.io/<Project-Name>`。`config.toml` 的設定很簡單，就寫這個專案 root 網址為何:

```yaml
baseURL = "https://<YOUR-GITHUB-USERNAME>.github.io/<PROJ>/"
```

`.github/workflows/deploy.yaml` 則要小心，這裡直接以我的為例，需要改兩個地方。

```yaml
on:
  push:
    branches:
      - main # 作者的範例是 hugo, 因為我有換 branch name 所以要改      
```

這樣，每當 push 行為發生在 `main` branch 上，就會觸發這個 action。 


```yaml
      - name: Deploy
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./public
          publish_branch: publish	# 作者預設是 master
          cname: brainynight.github.io # 不用把 proj name 也寫上去
```

## 預覽變更

Github Action 當中，已經把建立 graph (`hugo-obsidian`) 的步驟也包含上去了。但要發布之前我們總需要自己本地先看看。

作者其實有 makefile，應該可以 `make server`，會自動建立 graph 和 `hugo server`，或是懶得安裝 `make` 也可以直接打指令。以 windows 想複製 D 槽檔案為例: 

```bash
cp /d/Database/*.md content/notes
hugo-obsidian -input=content -output=assets/indices -index -root=.
hugo server --disableFastRender
```

