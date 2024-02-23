Nvim 有建 Python interface，需要下載模組 `pynvim`。可以下指令 `:h remote-plugin` 看官方給的教學，`:h python` 也有其他資訊。


## 如何確定當前的 Nvim 有支援 Python
Nvim 可以使用 `checkhealth` 得知
```
:checkhealth
```

## 如何確定當前的 Vim 有支援 Python
用 `:echo has("python")`, `:echo has("python3")` 來看是否支援 Python, Python3。

想看 Python 版本: `python import sys; print(sys.version)`。

