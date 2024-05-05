---
title: Keyword Extract
date: 2024-03-31 10:24
tags: []
---

Bart: Facebook 提出的 model，有分成不同的 size (base, large, ... )
提供 pretrained model，output 是 embedding vector，讓人拿來 fine tune 的。

https://tako-analytics.com/2023-06-19-how-to-extract-keywords-from-traditional-chinese-articles-in-nlp/#


https://huggingface.co/facebook/bart-base

## Tag/Keyword Extraction
- [Tech Keywords extractor](https://huggingface.co/ilsilfverskiold/tech-keywords-extractor)
	- Base on BartLarge，fine tune 在科技/Programming dataset 的感覺。
- [Bart keyword](https://huggingface.co/ilsilfverskiold/bart_keywords?text=This+model+is+a+fine-tuned+version+of+facebook%2Fbart-large+on+a+dataset+in+the+hub+called+sunhaozhepy%2Fag_news_keywords_embeddings+to+extract+main+keywords+from+text.+It+achieves+the+following+results+on+the+evaluation+set%3A)
	- 可能更好用，fine tune 的公開 dataset 有提供出來。
- [nandakishormpai/t5-small-github-repo-tag-generation](https://huggingface.co/nandakishormpai/t5-small-github-repo-tag-generation?text=What+time+is+it.)
	- 效果好嗎? 句子太簡短、像問句會變回答?