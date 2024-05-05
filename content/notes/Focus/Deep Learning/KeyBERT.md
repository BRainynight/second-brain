---
title: keyBERT
date: 2024-03-31 18:50
tags:
  - nlp
---
## 架構
- Input: 一段文字
1. 把 input doc 切成 tokenize words. 
2. 分別對 input doc 與 tokens 取 embeddings: 
	1. Doc -> doc level embeded vector. 
	2. tokens -> token embed vectors 
3. 逐一比較 token 跟 doc embeded vector 的 cosine similarity. 

![[KeyBERT.png]]
## 優點
- keyword 是直接切出來的，必定是文章內的文字，可信度高? 

## 替換 embedding model 
[Ref](https://tako-analytics.com/2023-06-19-how-to-extract-keywords-from-traditional-chinese-articles-in-nlp/#): 在 hugging face 上找到喜歡的 embedding 模型替換! 
```python
kw_model = KeyBERT(model='distiluse-base-multilingual-cased-v1')
keywords = kw_model.extract_keywords(docs,vectorizer=vectorizer)
```

## how to fine tunning pretrain model BART
https://medium.com/@ferlatti.aldo/fine-tuning-a-chat-summarizer-c18625bc817d
檢查 dataset，看起來是不用 ground truth ? 

---

## Compare with KeyBart
[KeyBart](https://huggingface.co/bloomberg/KeyBART?text=Hi+Hank%2C+%0D%0AIn+m12334%2Ftest%2Flayout%2C+connection+path+cannot+be+created+when+drag%2C+but+can+be+created+with+click.+%0D%0A---%0D%0AThe+root+cause+is+because+point+mode+filter+the+connetikon+path%2C+but+DnD+mode+doesn%27t.+%0D%0Athe+related+rule+is+maxOutSeq.) 是 bloomberg 提出的模型，在測試過程中，有 ground truth 關鍵字被部分擷取的問題。

