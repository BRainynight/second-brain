---
title: Vim and System Clipboard
date: 2023-12-26 23:22
tags: []
---

## 在 Linux Neovim 上面使用系統剪貼簿
1. 確認 `$DISPLAY` 有正確的數值
2. 確認 `xclip` 可執行
3. 在 init.nvim 中設置，意思是把 neovim 的剪貼簿連到 register `+`或  `*`
	```
	"choose 1
	set clipboard=unnamed  
	set clipboard=unnamedplus
	```
4. ff

### unnamed 與 unnamedplus 的差別
unmaed register 是 `*`，unnamedplus 是 `+`，兩者都是 system clipboard，差別在於
- unmaed register `*` : 在 Linux 中表示 selection clipboard
- unnamedplus register `+`: 就是真正的 copy paste 所放置的系統剪貼簿，在其他 OS 中也是如此。

[远程主机及本地主机之间共享 Clipboard，以及 Neovim 访问 Clipboard 全解析](https://shichunhui0924.medium.com/%E8%BF%9C%E7%A8%8B%E4%B8%BB%E6%9C%BA%E5%8F%8A%E6%9C%AC%E5%9C%B0%E4%B8%BB%E6%9C%BA%E4%B9%8B%E9%97%B4%E5%85%B1%E4%BA%AB-clipboard-%E4%BB%A5%E5%8F%8A-neovim-%E8%AE%BF%E9%97%AE-clipboard-%E5%85%A8%E8%A7%A3%E6%9E%90-f9040ebb8586)