---
title: Run AI Model Locally
date: 2024-04-15 21:02
tags: []
---
- [讓 LLM Model 可以快速變成地端服務 — Ollama](https://medium.com/@simon3458/ollama-llm-model-as-a-service-introduction-d849fb6d9ced)

## Ollama 
讓你從 Command Line 下載、啟動、執行模型

### Download ollama
```bash
curl -fsSL https://ollama.com/install.sh | sh
```


### 開始
1. 開一個視窗執行: 
	```
   ollama server
	```

2. 開另一個視窗執行
	```bash
ollama run gemma:2b
	```
	第一次執行會花比較多時間。
gemma 是 google 的開源版模型，本身就支援中文。
