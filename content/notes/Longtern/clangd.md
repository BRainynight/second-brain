---
title: clangd
date: 2024-03-04 19:26
tags:
  - empty
---
## CompileFlags
```
CompileFlags:                     # Tweak the parse settings
  Add: [-xc++, -Wall]             # treat all files as C++, enable more warnings
  Remove: -W*                     # strip all other warning-related flags
  Compiler: clang++               # Change argv[0] of compile flags to `clang++`
```

告訴 clangd 如何解讀當前的檔案，簡單來說，

像是 `clangd $filename` 並且加上相同的設定。但嚴格來說