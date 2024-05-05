---
title: Golang Miscs
date: 2024-05-05 12:05
tags:
  - empty
---

# Golang


## go: go.mod file not found in current directory or any parent directory

在嘗試安裝模組時出現問題，需要先 init module 再下 `mod get`

```
go mod init <current-dir-name>
```

https://www.techdatao.com/article/detail/57.html

![image-20231001224624854](img/Golang/image-20231001224624854.png)

## GOROOT and GOPATH

設置環境變數的方法
```
go env -w GO111MODULE=auto
```